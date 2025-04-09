#include "unchunkedlayer.h"
#include "../../../control/repository/blendrepository.h"


namespace PIPKA::IMAGE
{
UnchunkedLayer::UnchunkedLayer(int index, Color color, const Rectangle &rectangle) :
    Layer(rectangle),
    defaultColor(color), m_pixelBuffer(m_rect.bufferSize(), defaultColor)
{
    blend = CONTROL::TOOLS::BlendRepository::instance()->getBlend<COLOR::NormalBlend>();
    m_name = "Layer " + QString::number(index);
}

Color UnchunkedLayer::getColor(int x, int y)
{
    if (!m_rect.contains(x, y)) return 0;
    const int index = m_rect.bufferIndex(x, y);
    return m_pixelBuffer.at(index);
}

void UnchunkedLayer::setPixel(int x, int y, Color color)
{
    if (!m_rect.contains(x, y)) return;
    const int index = m_rect.bufferIndex(x, y);
    m_pixelBuffer.at(index) = color;
    emit pixelUpdated(x, y);
}

void UnchunkedLayer::addPixelColor(int x, int y, Color colorDifference)
{
    if (!m_rect.contains(x, y)) return;
    const int index = m_rect.bufferIndex(x, y);
    m_pixelBuffer.at(index) += colorDifference;
    emit pixelUpdated(x, y);
}

void UnchunkedLayer::subtractPixelColor(int x, int y, Color colorDifference)
{
    if (!m_rect.contains(x, y)) return;
    const int index = m_rect.bufferIndex(x, y);
    m_pixelBuffer.at(index) -= colorDifference;
    emit pixelUpdated(x, y);
}

void UnchunkedLayer::flipVisible()
{
    visibleFlag = !visibleFlag;
}

void UnchunkedLayer::setVisible(const bool flag)
{
    visibleFlag = flag;
}

void UnchunkedLayer::clearLayer()
{
    for (int index = 0; index < m_pixelBuffer.size(); ++index) {
        m_pixelBuffer[index] = 0;
    }
    emit rectangleUpdated(m_rect);
}
}
