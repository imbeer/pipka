#include "image.h"

#include <QImage>
#include <qdebug.h>

namespace PIPKA::IMAGE {

Image::Image(
    const int &w,
    const int &h)
    : w(w), h(h)
{
    m_layers = std::vector{
        std::make_shared<Layer>(0, w, h, 0xffffffff),
    };
    connect(m_layers.at(0).get(), &Layer::pixelChanged, this, &Image::mergePixel);
    connect(m_layers.at(0).get(), &Layer::fullLayerChanged, this, &Image::mergeAllPixels);
    m_mergedImage = m_layers.at(0)->pixels();
}

void Image::insertLayer(const int &index)
{
    m_layers.insert(m_layers.begin() + index, std::make_shared<Layer>(index, w, h, 0x00000000));
    connect(m_layers.at(index).get(), &Layer::pixelChanged, this, &Image::mergePixel);
    connect(m_layers.at(index).get(), &Layer::fullLayerChanged, this, &Image::mergeAllPixels);
    emit layerAdded(index);
}

void Image::pushBackLayer()
{
    insertLayer(m_layers.size());
}

QImage Image::toQImage() const
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

Color Image::renderPixel(const int &index) const
{
    Color baseColor = 0x00000000;
    for (const auto &layer : m_layers) {
        if (!layer->isVisible()) continue;
        const auto blend = layer->blend;
        baseColor = blend->blend(baseColor, layer->getColor(index));
    }
    // qDebug() << "pixel rendered";
    return baseColor;
}

void Image::mergePixel(const int &layerIndex, int x, int y)
{
    const auto pixelInd = x + y * w;
    m_mergedImage.at(pixelInd) = renderPixel(pixelInd);
    emit pixelChanged(x, y);
}

void Image::mergeAllPixels(const int &layerIndex)
{
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            const auto pixelInd = x + y * w;
            m_mergedImage.at(pixelInd) = renderPixel(pixelInd);
        }
    }
    emit allPixelsChanged();
}
}

