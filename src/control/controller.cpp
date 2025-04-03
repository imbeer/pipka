#include "controller.h"
#include "tools/rasterizer.h"
#include <qdebug.h>
#include <qvector3d.h>
#include <qvectornd.h>

#include "repositories/brushrepository.h"

namespace PIPKA::CONTROL {

Controller::Controller()
    : m_image(nullptr)
{
    m_versionControlSystem = std::make_shared<VERSIONCONTROL::VersionControlSystem>();
    // m_brush = std::make_shared<TOOLS::BRUSH::Brush>(std::make_shared<IMAGE::COLOR::NormalBlend>(), 0xFFFFFFFF);
    m_activeTool = std::make_shared<TOOLS::Rasterizer>(TOOLS::BrushRepository::instance()->activeBrush(), m_versionControlSystem);
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
    m_image->layers()[m_activeLayerIndex]->clearLayer();
}

void Controller::addLayer()
{
    // m_image->pushBackLayer();
    m_image->pushBackLayer();
    m_activeLayerIndex = m_image->layerSize() - 1;
    // m_image->layers()[m_activeLayerIndex]
}

void Controller::handleClick(const double &x, const double &y, const double &pressure)
{
    m_pressed = true;
    const QVector3D currentPoint = getCoordinates(x, y, pressure);

    if (isOutside(currentPoint)) return;

    m_activeTool->action(currentPoint, m_previousPoint, m_image->layers()[m_activeLayerIndex], m_image);
    m_previousPoint.emplace(currentPoint);
}

void Controller::handleRelease(const double &x, const double &y, const double &pressure)
{
    m_pressed = false;
    m_activeTool->release();
    m_previousPoint.reset();
    // m_rasterizer.drawPoint(m_image->layers()[m_activeLayerIndex], getCoordinates(x, y, pressure));
}

void Controller::handleMove(const double &x, const double &y, const double &pressure)
{
    if (!m_pressed) return;
    const QVector3D currentPoint = getCoordinates(x, y, pressure);

    if (isOutside(currentPoint)) {
        m_previousPoint.reset();
        return;
    }

    if (!m_previousPoint.has_value()) {
        m_activeTool->action(currentPoint, m_previousPoint, m_image->layers()[m_activeLayerIndex], m_image);
        m_previousPoint.emplace(currentPoint);
        return;
    }

    if (isFarEnough(currentPoint, *m_previousPoint)) {
        m_activeTool->action(currentPoint, m_previousPoint, m_image->layers()[m_activeLayerIndex], m_image);
        m_previousPoint.emplace(currentPoint);
    }
}

QVector3D Controller::getCoordinates(const double &x, const double &y, const double &pressure) const
{
    const double normalizedX = x * m_transform->m_i_mvp(0, 0) + y * m_transform->m_i_mvp(0, 1) - 1 * m_transform->m_i_mvp(0, 2);
    const double normalizedY = x * m_transform->m_i_mvp(1, 0) + y * m_transform->m_i_mvp(1, 1) + 1 * m_transform->m_i_mvp(1, 2);

    float imageX = (1 - normalizedX) * m_image->width() * 0.5f;
    float imageY = (normalizedY + 1) * m_image->height() * 0.5f;

    return {imageX, imageY, static_cast<float>(pressure)};
}



void Controller::undo() const
{
    m_versionControlSystem->undo();
}

void Controller::redo() const
{
    m_versionControlSystem->redo();
}



}
