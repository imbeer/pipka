#include "image.h"

#include <QImage>
#include <qdebug.h>

namespace PIPKA::IMAGE {

Image::Image(
    const int &w,
    const int &h)
    : w(w), h(h)
{
    m_layers = std::vector<std::shared_ptr<Layer>>{
        std::make_shared<Layer>(0, w, h, 0xff1e1e2e),
    };
    connect(m_layers.at(0).get(), &Layer::pixelChanged, this, &Image::mergePixel);
    m_mergedImage = m_layers.at(0)->pixels();
}

void Image::insertLayer(const int &index)
{
    m_layers.insert(m_layers.begin() + index, std::make_shared<Layer>(index, w, h, 0x00000000));
    connect(m_layers.at(index).get(), &Layer::pixelChanged, this, &Image::mergePixel);
    emit layerAdded(index);
}

void Image::pushBackLayer()
{
    m_layers.push_back(std::make_shared<Layer>(layerSize(), w, h, 0x00000000));
    emit layerAdded(layerSize() - 1);
}

QImage Image::toQImage()
{
    const int w = width();
    const int h = height();

    auto image = QImage(
        reinterpret_cast<const uchar*>(m_mergedImage.data()),
        w, h,
        w * sizeof(Color), // Bytes per line
        QImage::Format_ARGB32);
    image.mirror(false, true);
    return image;
}

Color Image::renderPixel(const int &index)
{
    Color baseColor = 0x00000000;
    for (const auto &layer : m_layers) {
        auto blend = layer->blend;
        baseColor = blend->blend(baseColor, layer->getColor(index));
    }
    return baseColor;
}

void Image::mergePixel(const int &layerIndex, const int &x, const int &y)
{
    const auto pixelInd = x + y * w;
    m_mergedImage.at(pixelInd) = renderPixel(pixelInd);
    emit pixelChanged(x, y);
}

}

