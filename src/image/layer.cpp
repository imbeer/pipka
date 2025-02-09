#include "layer.h"

#include <qdebug.h>
#include <random>

namespace PIPKA::IMAGE {

Layer::Layer(
    const int &index,
    const int &w,
    const int &h,
    const Color &color)
    : m_index(index), w(w), h(h), m_pixels(w * h, color), defaultColor(color)
{
    blend = std::make_shared<COLOR::NormalBlend>();
}

Color Layer::getColor(const int &x, const int &y)
{
    if (x >= w || x < 0 || y >= h || y < 0) return 0;
    const auto pixelInd = x + y * w;
    return m_pixels.at(pixelInd);
}

Color Layer::getColor(const int &index)
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
    // if (pixelInd >= m_pixels.size() || pixelInd < 0) return;
    m_pixels.at(pixelInd) = color;
}

void Layer::clearLayer()
{
    for (auto &pixel : m_pixels) {
        pixel = defaultColor;
    }
    update();
}

void Layer::update()
{
    emit fullLayerChanged(m_index);
}

}
