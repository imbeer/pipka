#include "rasterizer.h"
#include <qdebug.h>

#include <cmath>

namespace PIPKA::CONTROL::TOOLS {

Rasterizer::Rasterizer()
    : Tool()
{
    m_blend = std::make_shared<IMAGE::COLOR::NormalBlend>();
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
        layer->drawPixel(
            x, y,
            calculateColor(layer, m_color, x, y, currentPoint.z(), currentPoint.z(), 1));
        return;
    }

    drawLine(layer, *previousPoint, currentPoint);
}

void Rasterizer::release() {}

void Rasterizer::confirm() {}

void Rasterizer::drawLine(
    const LayerPtr layer,
    const QVector3D &start,
    const QVector3D &end)
{
    int startX = static_cast<int>(std::round(start.x()));
    int startY = static_cast<int>(std::round(start.y()));
    const int endX = static_cast<int>(std::round(end.x()));
    const int endY = static_cast<int>(std::round(end.y()));
    const double startPressure = start.z();
    const double endPressure = start.z();
    // qDebug() << "start pressure" << startPressure;
    // qDebug() << "end pressure" << endPressure;

    int deltaX = abs(endX - startX);
    int deltaY = abs(endY - startY);
    const int stepX = (startX < endX) ? 1 : -1;
    const int stepY = (startY < endY) ? 1 : -1;

    int errorTerm = deltaX - deltaY;
    int totalSteps = std::max(deltaX, deltaY);

    for (int currentStep = 1; currentStep <= totalSteps; ++currentStep) {
        float interpolation = static_cast<float>(currentStep) / totalSteps;
        layer->drawPixel(
            startX,
            startY,
            calculateColor(
                layer,
                m_color,
                startX, startY,
                startPressure, endPressure,
                interpolation));

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

Color Rasterizer::calculateColor(
    const LayerPtr layer,
    const Color &color,
    const int &x, const int &y,
    const double &startPressure, const double &endPressure,
    const float &interpolation) const {
    using namespace PIPKA::IMAGE;
    // todo: here should be a brush method or something, but for now
    const double pressure = std::clamp(interpolation * (endPressure - startPressure) + startPressure, 0.0, 1.0);

    const Color baseColor = layer->getColor(x, y);
    Color paintColor = color;

    auto alpha = COLOR::hexToFloat(COLOR::alpha(paintColor));
    alpha *= pressure;
    COLOR::setAlpha(paintColor, COLOR::floatToHex(alpha));

    return m_blend->blend(baseColor, paintColor);
}

}
