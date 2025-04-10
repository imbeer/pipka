#include "squarebrush.h"

namespace PIPKA::CONTROL::TOOLS::BRUSH
{
SquareBrush::SquareBrush(
    IMAGE::COLOR::Blend *blend,
    Color color) :
    Brush(blend, color)
{
    m_radius = 100;
    drawCallInterval = 10;
}

void SquareBrush::draw(
    std::shared_ptr<VERSIONCONTROL::PixelOperation> operation,
    int centerX, int centerY,
    float interpolation,
    float pressure,
    int deltaX, int deltaY)
{
    const auto colorDifferences = operation->getBuffer();
    const auto layer = operation->layer();
    const auto image = operation->image();

    for (int x = centerX - m_radius; x <= centerX + m_radius; x++) {
        for (int y = centerY - m_radius; y <= centerY + m_radius; y++) {
            if (colorDifferences->hasPixelOnCoordinate(x, y)) {
                continue; /// already drawn there
            }
            const auto colorDifference = calculateColors(layer, x, y, interpolation, pressure);
            layer->addPixelColor(x, y, colorDifference);
            image->mergePixel(x, y);
            colorDifferences->putPixel(x, y, colorDifference);
        }
    }
}

Color SquareBrush::calculateColors(
    const IMAGE::UnchunkedLayerPtr &layer,
    int x, int y,
    float interpolation,
    float pressure)
{
    return Brush::calculateColors(layer, x, y, interpolation, pressure);
}
}
