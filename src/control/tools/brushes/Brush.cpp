#include "Brush.h"
#include "QDebug"

namespace PIPKA::CONTROL::TOOLS::BRUSH
{

Brush::Brush(
    const std::shared_ptr<IMAGE::COLOR::Blend> &blend,
    const Color color)
    : blend(blend), color(color)
{
}

void Brush::draw(
    const LayerPtr &layer,
    const int centerX, const int centerY,
    const float interpolation,
    const float pressure,
    int deltaX, int deltaY)
{
    const Color color = getColor(layer, centerX, centerY, interpolation, 1.0f);
    // qDebug() << QString::number(color, 16);
    layer->drawPixel(centerX, centerY, color);
}

Color Brush::getColor(
    const LayerPtr &layer,
    const int x, const int y,
    float interpolation, const float pressure)
{
    const Color baseColor = layer->getColor(x, y);

    Color paintColor{layer->blend->blend(baseColor, color)};
    auto alpha = IMAGE::COLOR::hexToFloat(IMAGE::COLOR::alpha(paintColor));
    alpha *= pressure;
    IMAGE::COLOR::setAlpha(paintColor, IMAGE::COLOR::floatToHex(alpha));

    return paintColor;
}
}
