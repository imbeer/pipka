#include "temporarypixelbuffer.h"

namespace PIPKA::IMAGE::BUFFER
{
TemporaryPixelBuffer::TemporaryPixelBuffer(const Rectangle rectangle) :
    // m_pixelBuffer(rectangle.bufferSize(), 0x00000000),
    m_indexBuffer(0),
    m_fullRectangle(rectangle)
{ }

TemporaryPixelBuffer::~TemporaryPixelBuffer()
{ }

// bool TemporaryPixelBuffer::hasPixelOnCoordinate(int x, int y) const
// {
//     if (!m_fullRectangle.contains(x, y)) return true;
//     // return m_pixelBuffer[m_fullRectangle.bufferIndex(x, y)] != 0x00000000;
// }

void TemporaryPixelBuffer::putPixel(int x, int y, const Color color)
{
    if (!m_fullRectangle.contains(x, y)) return;
    const int index = m_fullRectangle.bufferIndex(x, y);
    // m_pixelBuffer[index] = color;
    m_indexBuffer.push_back({{x, y}, color});
    minX = std::min(x, minX);
    minY = std::min(y, minY);
    maxX = std::max(x, maxX);
    maxY = std::max(y, maxY);
}


}
