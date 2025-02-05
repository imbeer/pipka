#include "image.h"

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

}

