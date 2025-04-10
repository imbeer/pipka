#ifndef TEMPORARYPIXELBUFFER_H
#define TEMPORARYPIXELBUFFER_H
#include <limits>
#include "rectangle.h"
#include "../color/color.h"

namespace PIPKA::IMAGE::PIXELMAP
{

class TemporaryPixelBuffer
{
public:
    explicit TemporaryPixelBuffer(const Rectangle rectangle);
    ~TemporaryPixelBuffer();
    bool hasPixelOnCoordinate(int x, int y) const;
    void putPixel(int x, int y, Color color);
    Rectangle boundingBox() const { return {minX, minY, maxX - minX, maxY - minY}; }
    std::vector<Color> data() const { return m_pixelBuffer; }
    std::vector<std::pair<std::pair<int, int>, Color> > pixels() const { return m_indexBuffer; }
    void clearPixelBuffer() { m_pixelBuffer.clear(); }

private:
    std::vector<Color> m_pixelBuffer;
    std::vector<std::pair<std::pair<int, int>, Color> > m_indexBuffer;
    const Rectangle m_fullRectangle;
    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int maxY = std::numeric_limits<int>::min();
};

}
#endif //TEMPORARYPIXELBUFFER_H
