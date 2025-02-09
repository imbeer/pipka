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
}

void Image::insertLayer(const int &index)
{
    m_layers.insert(m_layers.begin() + index, std::make_shared<Layer>(index, w, h, 0x00000000));
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
    std::vector<Color> buffer(w * h, 0x00);

    auto start = std::chrono::high_resolution_clock::now();

    for (int pixelInd = 0; pixelInd < w * h; ++pixelInd) {
        Color baseColor = 0x00;
        for (const auto &layer : layers()) {
            baseColor = layer->blend->blend(baseColor, layer->getColor(pixelInd));
        }
        buffer.at(pixelInd) = baseColor;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    qDebug() << duration.count();

    auto image = QImage(
        reinterpret_cast<const uchar*>(buffer.data()),
        w, h,
        w * sizeof(Color), // Bytes per line
        QImage::Format_ARGB32);
    image.mirror(false, true);
    return image;
}

}

