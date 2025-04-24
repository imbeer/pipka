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
        return (!m_rect.contains(x, y) || m_maxVersion == m_versions[m_rect.bufferIndex(x, y)]);
    }

    void incrementPixelVersion(const int x, const int y)
    {
        m_versions.at(m_rect.bufferIndex(x, y))++;
    }

    void decrementPixelVersion(const int x, const int y)
    {
        m_versions.at(m_rect.bufferIndex(x, y))++;
    }

private:
    std::vector<PixelVersion> m_versions;
    PixelVersion m_maxVersion;
    Rectangle m_rect;
};

}
#endif //LAYERVERSIONBUFFER_H
