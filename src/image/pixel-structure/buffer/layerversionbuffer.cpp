#include "layerversionbuffer.h"

namespace PIPKA::IMAGE::BUFFER
{
LayerVersionBuffer::LayerVersionBuffer(const Rectangle &rectangle) :
    m_rect(rectangle), m_versions(rectangle.bufferSize(), 0), m_maxVersion(0)
{
    // todo: not optimazed. why.
}

}
