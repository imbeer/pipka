#include "pixelmap.h"

namespace PIPKA::IMAGE::PIXELMAP
{
PixelMap::PixelMap()
{ }

PixelMap::~PixelMap()
{ }

bool PixelMap::hasPixelOnCoordinate(int x, int y) const
{
    return m_data.contains({x, y}) != 0;
}

void PixelMap::putPixel(int x, int y, const Color color)
{
    m_data.insert({{x, y}, color});
    minX = std::min(x, minX);
    minY = std::min(y, minY);
    maxX = std::max(x, maxX);
    maxY = std::max(y, maxY);
}


}
