#include "rasterizer.h"
#include <qdebug.h>
#include <cmath>
#include "../repository/brushrepository.h"

namespace PIPKA::CONTROL::TOOLS {

Rasterizer::Rasterizer(
    const VersionControlPtr &versionControlSystem)
    : Tool(versionControlSystem)
{ }

void Rasterizer::action(
    const QVector3D &currentPoint,
    const optional<QVector3D> &previousPoint,
    const ImagePtr &image)
{
    const auto &layer = image->activeLayer();
    if (m_operation == nullptr || m_operation->layer() == nullptr) {
        m_operation = std::make_shared<VERSIONCONTROL::PixelOperation>(image, layer);
    }

    if (!previousPoint.has_value()) {
        const int x = static_cast<int>(currentPoint.x());
        const int y = static_cast<int>(currentPoint.y());
        BrushRepository::instance()->activeBrush()->draw(
            m_operation,
            x, y,
            1, currentPoint.z(),
            0, 0);
        image->mergedLayer()->update();
        return;
    }
    drawLine(*previousPoint, currentPoint);
    image->mergedLayer()->update();
}

void Rasterizer::release()
{
    m_versionControlSystem->addOperation(m_operation);
    // m_operation->apply();
    m_operation = nullptr;
}

void Rasterizer::confirm() {}

void Rasterizer::drawLine(
    const QVector3D &start,
    const QVector3D &end)
{
    int startX = static_cast<int>(std::round(start.x()));
    int startY = static_cast<int>(std::round(start.y()));
    const int endX = static_cast<int>(std::round(end.x()));
    const int endY = static_cast<int>(std::round(end.y()));
    const double startPressure = start.z();
    const double endPressure = start.z();

    int deltaX = abs(endX - startX);
    int deltaY = abs(endY - startY);
    const int stepX = (startX < endX) ? 1 : -1;
    const int stepY = (startY < endY) ? 1 : -1;

    int errorTerm = deltaX - deltaY;
    int totalSteps = std::max(deltaX, deltaY);

    int drawIntervalCount = 0;
    int drawInterval = BrushRepository::instance()->activeBrush()->drawInterval();
    if (totalSteps <= drawInterval) {
        drawInterval = 0;
    }
    for (int currentStep = 1; currentStep <= totalSteps; ++currentStep) {

        float interpolation = static_cast<float>(currentStep) / totalSteps;
        const float pressure = static_cast<float>(std::clamp(
            interpolation * (endPressure - startPressure) + startPressure,
            0.0, 1.0));

        if (drawIntervalCount == drawInterval) {
            BrushRepository::instance()->activeBrush()->draw(
                m_operation,
                startX, startY,
                interpolation, pressure,
                0, 0);
        }
        ++drawIntervalCount;
        if (drawIntervalCount > drawInterval) {
            drawIntervalCount = 0;
        }

        if (startX == endX && startY == endY) break;

        int doubleErrorTerm = 2 * errorTerm;
        if (doubleErrorTerm > -deltaY) {
            errorTerm -= deltaY;
            startX += stepX;
        }
        if (doubleErrorTerm < deltaX) {
            errorTerm += deltaX;
            startY += stepY;
        }

    }
}


}
