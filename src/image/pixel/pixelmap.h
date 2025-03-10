#ifndef PIXELMAP_H
#define PIXELMAP_H
#include <limits>
#include <map>
#include "../color/color.h"

namespace PIPKA::IMAGE::PIXELMAP
{

using Rect = std::tuple<int, int, int, int>;

class PixelMap {
public:
    PixelMap();
    ~PixelMap();
    bool hasPixelOnCoordinate(int x, int y) const;
    void putPixel(int x, int y, Color color);
    std::map<std::pair<int, int>, Color> getMap() const {return m_data;}
    Rect getBoundingBox() const {return {minX, minY, maxX-minX, maxY-minY};}

private:
    std::map<std::pair<int, int>, Color> m_data;
    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int maxY = std::numeric_limits<int>::min();
};
}
#endif //PIXELMAP_H
