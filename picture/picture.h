#ifndef PICTURE_H
#define PICTURE_H

#include "layer.h"
#include <QObject>

namespace PICTURE
{

class Picture : public QObject
{

Q_OBJECT
public:
    Picture();
    Picture(const int w, const int h);
    ~Picture();

    void createLayer();
    void createLayer(const int index);
    void removeLayer(const int index);
    Layer& activeLayer();
    void setActiveLayer(const int index);
    std::vector<Layer>& layers();

    inline int width() {return w;};
    inline int height() {return h;};

signals:
    void addedLayer();
    void removedLayer();

private:
    std::vector<Layer> layerStorage;
    int activeLayerIndex;
    int w;
    int h;
};

}
#endif // PICTURE_H
