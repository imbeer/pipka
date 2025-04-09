#ifndef IMAGE_H
#define IMAGE_H

#include "layer/chunkedlayer.h"
#include "layer/unchunkedlayer.h"
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
    std::vector<std::shared_ptr<UnchunkedLayer>> layers() {return m_layers;}
    ChunkedLayerPtr mergedLayer() const { return m_mergedChunkedLayer; }
    UnchunkedLayerPtr activeLayer() const { return m_activeLayer; }

public:
    void mergeChunk(int xInd, int yInd) const;
    void mergePixel(int x, int y) const;
    void mergeRectangle(const Rectangle &rectangle) const;

private:
    Color renderPixel(int pointX, int pointY) const;
    void connectLayer(const UnchunkedLayerPtr &layer);

signals:
    void layerAdded(int index);

public:
    const Rectangle rect;

private:
    std::vector<UnchunkedLayerPtr> m_layers;
    UnchunkedLayerPtr m_activeLayer;
    ChunkedLayerPtr m_mergedChunkedLayer;
    UnchunkedLayerPtr m_mergedUnChunkedLayer;
};

using ImagePtr = std::shared_ptr<Image>;


}

#endif // IMAGE_H
