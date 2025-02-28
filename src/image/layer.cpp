#include "layer.h"

#include <qdebug.h>
#include <random>

namespace PIPKA::IMAGE {

Layer::Layer(
    const int &index,
    const int &w,
    const int &h,
    const Color &color)
    : m_pixels(w * h, color), w(w), h(h), defaultColor(color), m_index(index)
{
    blend = std::make_shared<COLOR::NormalBlend>();
    m_name = "Layer" + QString::number(index);
}

Color Layer::getColor(const int &x, const int &y) const
{
    if (x >= w || x < 0 || y >= h || y < 0) return 0;
    const auto pixelInd = x + y * w;
    return m_pixels.at(pixelInd);
}

Color Layer::getColor(const int &index) const
{
    if (index < 0 || index >= m_pixels.size()) return 0;
    return m_pixels.at(index);
}

void Layer::testDifferentPixels()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint32_t> dis(0, UINT32_MAX);
    for (auto &pixel : m_pixels) {
        pixel = dis(gen);
    }
    emit fullLayerChanged(m_index);
}

void Layer::drawPixel(const int &x, const int &y, const Color &color)
{
    if (x >= w || x < 0 || y >= h || y < 0) return;
    const auto pixelInd = x + y * w;
    m_pixels.at(pixelInd) = color;
    emit pixelChanged(m_index, x, y);
}

void Layer::clearLayer()
{
    for (auto &pixel : m_pixels) {
        pixel = defaultColor;
    }
    emit fullLayerChanged(m_index);
}

void Layer::update()
{
    emit fullLayerChanged(m_index);
}

}
