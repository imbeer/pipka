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
{}

// Layer::Layer(const Layer &layer)
//     : index(layer.index), w(layer.w), h(layer.h), m_pixels(layer.m_pixels) // todo: the fuck is wrong with this copy constructors
// {}

Color Layer::getColor(const int &x, const int &y)
{
    const auto pixelInd = x + y * w;
    return m_pixels.at(pixelInd);
}


void Layer::testDifferentPixels()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint32_t> dis(0, UINT32_MAX);
    for (auto &pixel : m_pixels) {
        pixel = dis(gen);
    }
    // qDebug() <<"layer changed";
    // qDebug() << m_index;
    emit layerChanged(m_index);
}

void Layer::drawPixel(const int &x, const int &y, const Color &color)
{
    const auto pixelInd = x + y * w;
    if (pixelInd > m_pixels.size() || pixelInd < 0) return;
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
    emit layerChanged(m_index);
}

}
