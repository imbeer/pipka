#ifndef PICTURE_H
#define PICTURE_H

#include "layer.h"

namespace PICTURE
{

class Picture
{
public:
    Picture(const int w, const int h);
    ~Picture();

    void createLayer();
    void createLayer(const int index);
    void removeLayer(const int index);
    Layer& activeLayer();
    void setActiveLayer(const int index);
    std::vector<Layer>& layers();

private:
    std::vector<Layer> layerStorage;
    int activeLayerIndex;
    int w;
    int h;
};

}
#endif // PICTURE_H
