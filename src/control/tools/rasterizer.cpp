#include "rasterizer.h"
#include <qdebug.h>

#include <cmath>

namespace PIPKA::CONTROL::TOOLS {

Rasterizer::Rasterizer()
    : Tool()
{
    m_brush = std::make_shared<BRUSH::Brush>(std::make_shared<IMAGE::COLOR::NormalBlend>(), 0xFF00FFFF);
}

void Rasterizer::action(
    const QVector3D &currentPoint,
    const optional<QVector3D> &previousPoint,
    const LayerPtr &layer,
    const ImagePtr &image)
{
    if (!previousPoint.has_value()) {
        const int x = static_cast<int>(currentPoint.x());
        const int y = static_cast<int>(currentPoint.y());
        m_brush->draw(
            layer,
            x, y,
            1, currentPoint.z(),
            0, 0);

        return;
    }
    drawLine(layer, *previousPoint, currentPoint);
}

void Rasterizer::release() {}

void Rasterizer::confirm() {}

void Rasterizer::drawLine(
    const LayerPtr &layer,
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

    for (int currentStep = 1; currentStep <= totalSteps; ++currentStep) {
        float interpolation = static_cast<float>(currentStep) / totalSteps;
        const float pressure = static_cast<float>(std::clamp(
            interpolation * (endPressure - startPressure) + startPressure,
            0.0, 1.0));

        m_brush->draw(
            layer,
            startX, startY,
            interpolation, pressure,
            0, 0);

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
