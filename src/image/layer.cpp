#include "layer.h"

#include <qdebug.h>

namespace PIPKA::IMAGE {

Layer::Layer(
    const int &w,
    const int &h,
    const Color &color)
    : w(w), h(h), m_pixels(w * h, color)
{
    for (const auto &pixel : m_pixels)
        qDebug() << pixel;
    qDebug() << m_pixels.size();
}

}
