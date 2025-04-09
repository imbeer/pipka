#include "controller.h"
#include "tools/rasterizer.h"
#include <qdebug.h>
#include <qvectornd.h>

#include "repositories/brushrepository.h"

namespace PIPKA::CONTROL {

Controller::Controller()
    : m_image(nullptr), m_transform(nullptr)
{
    m_versionControlSystem = std::make_shared<VERSIONCONTROL::VersionControlSystem>();
    m_activeTool = std::make_shared<TOOLS::Rasterizer>(m_versionControlSystem);
}

void Controller::createImage(const int &w, const int &h)
{
    if (!m_image) {
        m_image = std::make_shared<IMAGE::Image>(w, h);
    } else {
        qDebug() << "image already exists";
    }

    m_transform = std::make_shared<Transform>(m_image);

    m_transform->updateTransform();
    m_transform->updateProjection(1);
}

void Controller::saveImage(const QString &path) const
{
    if (m_image->toQImage().save(path, "PNG")) {
        qDebug() << "image saved";
    }
}

void Controller::clearActiveLayer() const
{
    m_image->activeLayer()->clearLayer();
}

void Controller::handleClick(const double &x, const double &y, const double &pressure)
{
    m_pressed = true;
    const QVector3D currentPoint = coordinates(x, y, pressure);

    if (image()->rect.contains(currentPoint)) return;

    m_activeTool->action(currentPoint, m_previousPoint, m_image);
    m_previousPoint.emplace(currentPoint);
}

void Controller::handleRelease(const double &x, const double &y, const double &pressure)
{
    m_pressed = false;
    m_activeTool->release();
    m_previousPoint.reset();
}

void Controller::handleMove(const double &x, const double &y, const double &pressure)
{
    if (!m_pressed) return;
    const QVector3D currentPoint = coordinates(x, y, pressure);

    if (!m_previousPoint.has_value()) {
        m_activeTool->action(currentPoint, m_previousPoint, m_image);
        m_previousPoint.emplace(currentPoint);
        return;
    }

    if (isFarEnough(currentPoint, *m_previousPoint)) {
        m_activeTool->action(currentPoint, m_previousPoint, m_image);
        m_previousPoint.emplace(currentPoint);
    }
}

QVector3D Controller::coordinates(const double &x, const double &y, const double &pressure) const
{
    const double normalizedX = x * m_transform->m_i_mvp(0, 0) + y * m_transform->m_i_mvp(0, 1) - 1 * m_transform->m_i_mvp(0, 2);
    const double normalizedY = x * m_transform->m_i_mvp(1, 0) + y * m_transform->m_i_mvp(1, 1) + 1 * m_transform->m_i_mvp(1, 2);

    float imageX = (1 - normalizedX) * m_image->width() * 0.5f;
    float imageY = (normalizedY + 1) * m_image->height() * 0.5f;

    return {imageX, imageY, static_cast<float>(pressure)};
}

}
