#include "rasterizer.h"
#include <qdebug.h>
#include <qimage.h>

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
        int x = static_cast<int>(currentPoint.x());
        int y = static_cast<int>(currentPoint.y());
        layer->drawPixel(
            x, y,
            calculateColor(layer, m_color, x, y, currentPoint.z(), currentPoint.z(), 1));
        layer->update();
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
    int startX = static_cast<int>(round(start.x()));
    int startY = static_cast<int>(round(start.y()));
    int endX = static_cast<int>(round(end.x()));
    int endY = static_cast<int>(round(end.y()));
    double startPressure = start.z();
    double endPressure = start.z();
    // qDebug() << "start pressure" << startPressure;
    // qDebug() << "end pressure" << endPressure;

    int deltaX = abs(endX - startX);
    int deltaY = abs(endY - startY);
    int stepX = (startX < endX) ? 1 : -1;
    int stepY = (startY < endY) ? 1 : -1;

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
    layer->update();
}

Color Rasterizer::calculateColor(
    const LayerPtr layer,
    const Color &color,
    const int &x, const int &y,
    const double &startPressure, const double &endPressure,
    const float &interpolation)
{
    using namespace PIPKA::IMAGE;
    // todo: here should be a brush method or something, but for now
    const double pressure = std::clamp(interpolation * (endPressure - startPressure) + startPressure, 0.0, 1.0);

    Color baseColor = layer->getColor(x, y);
    Color paintColor = color;

    auto alpha = COLOR::alpha(paintColor);
    alpha *= pressure;
    COLOR::setAlpha(paintColor, alpha);

    return m_blend->blend(baseColor, paintColor);
}

}
