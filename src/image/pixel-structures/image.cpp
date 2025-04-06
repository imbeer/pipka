#include "image.h"

#include <QImage>
#include <qdebug.h>

namespace PIPKA::IMAGE {

Image::Image(int w, int h) : rect(0, 0, w, h)
{
    m_layers.push_back(
        std::make_shared<Layer>(0, 0xffffffff, rect)
    );
    // connectLayer(0)
    connectLayer(m_layers[0]);
    qDebug() << m_layers.size();
    m_activeLayer = m_layers[0];
    m_mergedLayer = std::make_shared<Layer>(0, 0xffffffff, rect);
    // connect(m_layers.at(0).get(), &Layer::pixelChanged, this, &Image::mergePixel);
    // connect(m_layers.at(0).get(), &Layer::fullLayerChanged, this, &Image::mergeAllPixels);
    // m_mergedImage = m_layers.at(0)->pixels();
}

void Image::insertLayer(int index)
{
    m_layers.insert(
        m_layers.begin() + index,
        std::make_shared<Layer>(index, 0x00000000, rect));
    connectLayer(m_layers[index]);
    emit layerAdded(index);
}

void Image::pushBackLayer()
{
    insertLayer(m_layers.size());
}

void Image::setActiveLayer(const int index)
{
    m_activeLayer = m_layers.at(index);
}

QImage Image::toQImage() const
{
    // const int w = width();
    // const int h = height();

    // auto image = QImage(
    //     reinterpret_cast<const uchar*>(m_mergedImage.data()),
    //     w, h,
    //     w * sizeof(Color), // Bytes per line
    //     QImage::Format_ARGB32);
    // image.mirror(false, true);
    return QImage();
}

Color Image::renderPixel(const int pointX, const int pointY) const
{
    Color baseColor = 0x00000000;
    for (const auto &layer : m_layers) {
        if (!layer->isVisible()) continue;
        const auto blend = layer->blend;
        baseColor = blend->blend(baseColor, layer->getColor(pointX, pointY));
    }
    return baseColor;
}

void Image::mergeChunk(const int xInd, const int yInd) const
{
    const auto chunkToUpdate = m_mergedLayer->getChunk(xInd, yInd);
    for (int x = chunkToUpdate->rect.x; x < chunkToUpdate->rect.x + chunkToUpdate->rect.w; ++x) {
        for (int y = chunkToUpdate->rect.y; y < chunkToUpdate->rect.y + chunkToUpdate->rect.h; ++y) {
            chunkToUpdate->setPixel(x, y, renderPixel(x, y));
        }
    }
    chunkToUpdate->update();
}

void Image::connectLayer(const LayerPtr &layer)
{
    for (auto &chunks : layer->chunks()) {
        for (auto &chunkPtr : chunks) {
            connect(
                chunkPtr.get(), &Chunk::updated,
                this, &Image::mergeChunk);
        }
    }

}
}

