#ifndef LAYERVERSIONBUFFER_H
#define LAYERVERSIONBUFFER_H

#include <vector>
#include <cstdint>

#include "../rectangle.h"

namespace PIPKA::IMAGE::BUFFER
{

using PixelVersion = std::uint64_t;

class LayerVersionBuffer
{
public:
    LayerVersionBuffer(const Rectangle &rectangle);
    void incrementVersion() { ++maxVersion; } // todo: check if overflow.
    bool isPixelUpdated(int x, int y) const
    {
        if (m_rectangle.contains(x, y)) return true;
        return maxVersion == m_versions[m_rectangle.bufferIndex(x, y)];
    }

private:
    std::vector<PixelVersion> m_versions;
    PixelVersion maxVersion;
    Rectangle m_rectangle;
};

}
#endif //LAYERVERSIONBUFFER_H
