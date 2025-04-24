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
    explicit LayerVersionBuffer(const Rectangle &rectangle);
    void incrementTotalVersion() { m_maxVersion++; } // todo: check if overflow.

    [[nodiscard]] bool isPixelUpdated(const int x, const int y) const
    {
        if (!m_rect.contains(x, y)) {
            return true; /// do not draw here, there is no such point on layer
        }
        return m_maxVersion <= m_versions[m_rect.bufferIndex(x, y)];
    }

    void incrementPixelVersion(const int x, const int y)
    {
        m_versions[m_rect.bufferIndex(x, y)] = m_maxVersion;
    }

    void decrementPixelVersion(const int x, const int y)
    {
        m_versions[m_rect.bufferIndex(x, y)] = m_maxVersion;
    }

private:
    std::vector<PixelVersion> m_versions;
    PixelVersion m_maxVersion;
    Rectangle m_rect;
};

}
#endif //LAYERVERSIONBUFFER_H
