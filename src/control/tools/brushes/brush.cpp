#include "brush.h"
#include "QDebug"

namespace PIPKA::CONTROL::TOOLS::BRUSH
{

Brush::Brush(
    const std::shared_ptr<IMAGE::COLOR::Blend> &blend,
    const Color color)
    : m_blend(blend), m_color(color)
{ }

void Brush::draw(
    std::shared_ptr<VERSIONCONTROL::PixelOperation> operation,
    const int centerX, const int centerY,
    const float interpolation,
    const float pressure,
    int deltaX, int deltaY)
{
    auto colorDifferences = operation->getMap();
    if (colorDifferences->hasPixelOnCoordinate(centerX, centerY)) {
        return; /// already drawn there
    }

    const auto layer = operation->getLayer();
    const Color colorDifference = getColorDifference(layer, centerX, centerY, interpolation, 1.0f);
    // qDebug() << QString::number(color, 16);
    layer->addPixelColor(centerX, centerY, colorDifference);
    colorDifferences->putPixel(centerX, centerY, colorDifference);
}

Color Brush::getColorDifference(
    const LayerPtr &layer,
    const int x, const int y,
    float interpolation, const float pressure)
{
    const Color baseColor = layer->getColor(x, y);

    Color paintColor{m_blend->blend(baseColor, m_color)};
    auto alpha = IMAGE::COLOR::hexToFloat(IMAGE::COLOR::alpha(paintColor));
    alpha *= pressure;
    IMAGE::COLOR::setAlpha(paintColor, IMAGE::COLOR::floatToHex(alpha));

    paintColor -= baseColor;

    return paintColor;
}
}
