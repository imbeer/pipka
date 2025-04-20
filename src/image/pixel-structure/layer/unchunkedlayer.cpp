#include "unchunkedlayer.h"
#include "../../../control/repository/blendrepository.h"


namespace PIPKA::IMAGE
{
UnchunkedLayer::UnchunkedLayer(const int index, const Color color, const Rectangle &rectangle) :
    Layer(rectangle),
    defaultColor(color),
    m_pixelBuffer(m_rect.bufferSize(), defaultColor),
    m_versions(std::make_shared<BUFFER::LayerVersionBuffer>(m_rect))
{
    blend = CONTROL::TOOLS::BlendRepository::instance()->getBlend<COLOR::NormalBlend>();
    m_name = "Layer " + QString::number(index);
    // m_versions = std::make_shared<BUFFER::LayerVersionBuffer>(m_rect);
}

Color UnchunkedLayer::getColor(const int x, const int y)
{
    if (!m_rect.contains(x, y)) return 0;
    const int index = m_rect.bufferIndex(x, y);
    return m_pixelBuffer.at(index);
}

void UnchunkedLayer::setPixel(const int x, const int y, const Color color)
{
    if (!m_rect.contains(x, y)) return;
    const int index = m_rect.bufferIndex(x, y);
    m_pixelBuffer.at(index) = color;
    m_versions->updatePixel(x, y);
    // emit pixelUpdated(x, y);
}

void UnchunkedLayer::addPixelColor(const int x, const int y, const Color colorDifference)
{
    if (!m_rect.contains(x, y)) return;
    const int index = m_rect.bufferIndex(x, y);
    m_pixelBuffer.at(index) += colorDifference;
    m_versions->updatePixel(x, y);
    // emit pixelUpdated(x, y);
}

void UnchunkedLayer::subtractPixelColor(const int x, const int y, const Color colorDifference)
{
    if (!m_rect.contains(x, y)) return;
    const int index = m_rect.bufferIndex(x, y);
    m_pixelBuffer.at(index) -= colorDifference;
    m_versions->updatePixel(x, y);
    // emit pixelUpdated(x, y);
}

void UnchunkedLayer::addRectangle(const Rectangle &rectangle, const Color *pixelBuffer)
{
    for (int x = rectangle.x; x <= rectangle.w + rectangle.x; ++x) {
        for (int y = rectangle.y; y <= rectangle.h + rectangle.y; ++y) {
            m_pixelBuffer[m_rect.bufferIndex(x, y)] += pixelBuffer[m_rect.bufferIndex(x, y)];
        }
    }
    emit rectangleUpdated(rectangle);
}

void UnchunkedLayer::subtractRectangle(const Rectangle &rectangle, const Color *pixelBuffer)
{
    for (int x = rectangle.x; x <= rectangle.w + rectangle.x; ++x) {
        for (int y = rectangle.y; y <= rectangle.h + rectangle.y; ++y) {
            // subtractPixelColor(x, y, pixelBuffer[rectangle.bufferIndex(x, y)]);
            m_pixelBuffer[m_rect.bufferIndex(x, y)] -= pixelBuffer[m_rect.bufferIndex(x, y)];
        }
    }
    emit rectangleUpdated(rectangle);
}

void UnchunkedLayer::flipVisible()
{
    visibleFlag = !visibleFlag;
    emit rectangleUpdated(m_rect);
}

void UnchunkedLayer::setVisible(const bool flag)
{
    visibleFlag = flag;
    emit rectangleUpdated(m_rect);
}

void UnchunkedLayer::clearLayer()
{
    for (int index = 0; index < m_pixelBuffer.size(); ++index) {
        m_pixelBuffer[index] = 0;
    }
    emit rectangleUpdated(m_rect);
}
}
