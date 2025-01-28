#include "image.h"

namespace PIPKA::IMAGE {

Image::Image(
    const int &w,
    const int &h)
    : w(w), h(h)
{
    m_layers = std::vector<std::shared_ptr<Layer>>{std::make_shared<Layer>(0, w, h, 0xFF00FFF)};
}

}
