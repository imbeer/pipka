#ifndef IMAGE_H
#define IMAGE_H

#include "layer.h"
#include <vector>

namespace PIPKA::IMAGE {

class Image : public QObject
{
    Q_OBJECT
public:
    Image(int w, int h);

    void insertLayer(int index);
    void pushBackLayer();
    void setActiveLayer(int index);
    QImage toQImage() const;

    int width() const {return rect.w;}
    int height() const {return rect.h;}
    float ratio() const {return static_cast<float>(rect.w) / rect.h;}
    int layerSize() const {return m_layers.size();}
    std::vector<std::shared_ptr<Layer>> layers() {return m_layers;}
    LayerPtr mergedLayer() const { return m_mergedLayer; }
    LayerPtr activeLayer() const { return m_activeLayer; }

private:
    Color renderPixel(int pointX, int pointY) const;
    void mergeChunk(int xInd, int yInd) const;
    void connectLayer(const LayerPtr &layer);

signals:
    void layerAdded(int index);

public:
    const Rectangle rect;

private:
    std::vector<LayerPtr> m_layers;
    LayerPtr m_activeLayer;
    LayerPtr m_mergedLayer;
};

using ImagePtr = std::shared_ptr<Image>;


}

#endif // IMAGE_H
