#include "layer.h"

#include <qdebug.h>
#include <random>

namespace PIPKA::IMAGE {

Layer::Layer(
    const int &w,
    const int &h,
    const Color &color)
    : w(w), h(h), m_pixels(w * h, color)
{}

void Layer::testDifferentPixels()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint32_t> dis(0, UINT32_MAX);
    for (auto &pixel : m_pixels) {
        pixel = dis(gen);
    }
    emit layerChanged();
    // for (auto &pixel : m_pixels) {
    //     qDebug() << pixel;
    // }
    // qDebug() << m_pixels.size();
}

}
