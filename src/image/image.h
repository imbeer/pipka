#ifndef IMAGE_H
#define IMAGE_H

#include "layer.h"
#include <vector>

namespace PIPKA::IMAGE {

class Image
{
public:
    Image(
        const int &w,
        const int &h);
    inline const int width() {return w;};
    inline const int height() {return h;};
    inline std::vector<std::shared_ptr<Layer>> layers() {return m_layers;};
    inline const int layerSize() {return m_layers.size();};

private:
    const int w;
    const int h;

    std::vector<std::shared_ptr<Layer>> m_layers;
};

}

#endif // IMAGE_H
