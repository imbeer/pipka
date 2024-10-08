#include "picture.h"

namespace PICTURE
{

Picture::Picture()
{}

Picture::Picture(const int w, const int h)
{
    this->w = w;
    this->h = h;
    createLayer();
}

Picture::~Picture() {}

void Picture::createLayer()
{
    layerStorage.push_back(Layer(w, h));
    setActiveLayer(layerStorage.size() - 1);
    emit addedLayer();
}

void Picture::createLayer(const int index)
{
    if (index >= layerStorage.size() || index < 0) return;
    layerStorage.insert(layerStorage.begin() + index, Layer(w, h));
    setActiveLayer(index);
    emit addedLayer();
}

void Picture::removeLayer(const int index)
{
    if (index >= layerStorage.size() || index < 0) return;
    layerStorage.erase(layerStorage.begin() + index);
    emit removedLayer();
}

Layer& Picture::activeLayer()
{
    return layerStorage.at(activeLayerIndex);
}

void Picture::setActiveLayer(const int index)
{
    if (index >= layerStorage.size() || index < 0) return;
    activeLayerIndex = index;
}

std::vector<Layer>& Picture::layers()
{
    return layerStorage;
}
}
