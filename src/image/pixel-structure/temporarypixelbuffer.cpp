#include "temporarypixelbuffer.h"

namespace PIPKA::IMAGE::PIXELMAP
{
TemporaryPixelBuffer::TemporaryPixelBuffer(const Rectangle rectangle) :
    m_pixelBuffer(rectangle.bufferSize(), 0x00000000), m_fullRectangle(rectangle)
{ }

TemporaryPixelBuffer::~TemporaryPixelBuffer()
{ }

bool TemporaryPixelBuffer::hasPixelOnCoordinate(int x, int y) const
{
    // return m_data.contains({x, y}) != 0;
    if (!m_fullRectangle.contains(x, y)) return true;
    return m_pixelBuffer[m_fullRectangle.bufferIndex(x, y)] != 0x00000000;
}

void TemporaryPixelBuffer::putPixel(int x, int y, const Color color)
{
    if (!m_fullRectangle.contains(x, y)) return;
    m_pixelBuffer.at(m_fullRectangle.bufferIndex(x, y)) = color;
    // m_data.insert({{x, y}, color});
    minX = std::min(x, minX);
    minY = std::min(y, minY);
    maxX = std::max(x, maxX);
    maxY = std::max(y, maxY);
}


}
