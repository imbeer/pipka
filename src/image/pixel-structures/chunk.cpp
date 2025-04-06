#include "chunk.h"

namespace PIPKA::IMAGE
{
Chunk::Chunk(
    const int x, const int y,
    const int w, const int h,
    const int xInd, const int yInd,
    const Color initColor, const Rectangle &layerRect) :
    rect(x, y, w, h, layerRect),
    initColor(initColor),
    m_pixelBuffer(rect.bufferSize(), initColor),
    m_xInd(xInd), m_yInd(yInd)
{ }

Color Chunk::getPixel(const int pointX, const int pointY) const
{
    if (!rect.contains(pointX, pointY))
        throw std::out_of_range("Point is out of range");
    return m_pixelBuffer[rect.bufferIndex(pointX, pointY)];
}

void Chunk::setPixel(const int pointX, const int pointY, const Color color)
{
    if (!rect.contains(pointX, pointY))
        return;
    m_pixelBuffer[rect.bufferIndex(pointX, pointY)] = color;
}

void Chunk::clear()
{
    for (int i = 0; i < rect.bufferSize(); ++i) {
        m_pixelBuffer[i] = initColor;
    }
}
}
