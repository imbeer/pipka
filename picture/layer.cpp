#include "layer.h"

namespace PICTURE
{

Layer::Layer(int w, int h)
{
    this->w = w;
    this->h = h;
}

Layer::~Layer() {
    buffer.clear();
}

pixelRGBA_f* Layer::pixels()
{
    return buffer.data();
}

pixelRGBA_f* Layer::pixel(const int x, const int y)
{
    const int index = convertCoordsInIndex(x, y);
    if (index >= buffer.size() || index < 0) return nullptr;
    return &buffer.at(index);
}

void Layer::setPixel(const int x, const int y, const pixelRGBA_f pixel)
{
    const int index = convertCoordsInIndex(x, y);
    if (index >= buffer.size() || index < 0) return;
    buffer[index] = pixel;
}
}
