#include "brush.h"
#include "QDebug"

namespace PIPKA::CONTROL::TOOLS::BRUSH
{

Brush::Brush(
    IMAGE::COLOR::Blend *blend,
    const Color color)
    : m_blend(blend), m_color(color)
{ }

void Brush::setColor(const Color color)
{
    m_color = color;
}

void Brush::setBlend(IMAGE::COLOR::Blend *blend)
{
    m_blend = blend;
}

void Brush::draw(
    std::shared_ptr<VERSIONCONTROL::PixelOperation> operation,
    const int centerX, const int centerY,
    const float interpolation,
    const float pressure,
    int deltaX, int deltaY)
{
    const auto colorDifferences = operation->pixels();
    if (operation->versions()->isPixelUpdated(centerX, centerY)) {
        return; /// already drawn there
    }

    const auto layer = operation->layer();
    const auto colorDifference = calculateColors(layer, centerX, centerY, interpolation, pressure);
    layer->addPixelColor(centerX, centerY, colorDifference);
    colorDifferences->putPixel(centerX, centerY, colorDifference);
}

Color Brush::calculateColors(
    const IMAGE::UnchunkedLayerPtr &layer,
    const int x, const int y,
    float interpolation, const float pressure)
{
    const Color baseColor = layer->getColor(x, y);

    Color paintColor = m_color;
    float alpha = IMAGE::COLOR::hexToFloat(IMAGE::COLOR::alpha(paintColor));
    alpha *= pressure;
    IMAGE::COLOR::setAlpha(paintColor, IMAGE::COLOR::floatToHex(alpha));

    paintColor = m_blend->blend(baseColor, paintColor);
    paintColor -= baseColor;
    return paintColor;
}
}
