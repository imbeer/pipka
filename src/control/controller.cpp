#include "controller.h"
#include <qdebug.h>
#include <qvectornd.h>

namespace PIPKA::CONTROL {

Controller::Controller() :
    QObject(nullptr),
    m_image(nullptr),
    m_transform(nullptr)
{
    m_versionControlSystem = TOOLS::ToolRepository::instance()->versionControl();
}

void Controller::createImage(const int &w, const int &h)
{
    if (m_image) {
        qDebug() << "Destroying image.";
        // todo: something for save
        // saveImage();
    }

    m_image = std::make_shared<IMAGE::Image>(w, h);
    if (!m_transform) {
        m_transform = std::make_shared<Transform>(m_image);
        m_transform->updateTransform();
    } else {
        m_transform->setImage(m_image);
    }
    m_transform->updateProjection(1);
    emit imageCreated();
}

void Controller::saveImage(const QString &path) const
{
    const QImage *image = m_image->toQImage();
    if (image->save(path, "PNG")) {
        qDebug() << "image saved";
    }
    delete image;
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

    activeTool()->action(currentPoint, m_previousPoint, m_image, m_transform);
    m_previousPoint.emplace(currentPoint);
    emit updated();
}

void Controller::handleRelease(const double &x, const double &y, const double &pressure)
{
    m_pressed = false;
    activeTool()->release();
    m_previousPoint.reset();
    emit updated();
}

void Controller::handleMove(const double &x, const double &y, const double &pressure)
{
    if (!m_pressed) return;
    const QVector3D currentPoint = coordinates(x, y, pressure);

    if (!m_previousPoint.has_value()) {
        activeTool()->action(currentPoint, m_previousPoint, m_image, m_transform);
        m_previousPoint.emplace(currentPoint);
        return;
    }

    if (isFarEnough(currentPoint, *m_previousPoint)) {
        activeTool()->action(currentPoint, m_previousPoint, m_image, m_transform);
        m_previousPoint.emplace(currentPoint);
    }
    emit updated();
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
