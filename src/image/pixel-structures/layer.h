#ifndef LAYER_H
#define LAYER_H
#include <set>
#include <vector>

#include "chunk.h"
#include "../color/color.h"
#include "../color/blend.h"
#include "pixelmap.h"

namespace PIPKA::IMAGE {

class Layer : public QObject
{
    Q_OBJECT
public:
    Layer(
        int index,
        Color color,
        const Rectangle &rectangle);

private:
    void splitToChunks();

public:

    int width() const {return m_rect.w;}
    int height() const {return m_rect.h;}
    QString name() {return m_name;}
    void setName(const QString &name) {m_name = name;}

    ChunkPtr getChunkOfPoint(int pointX, int pointY);
    ChunkPtr getChunk(int xInd, int yInd);
    const std::vector<std::vector<ChunkPtr>> &chunks() const { return m_chunks; }
    Color getColor(int x, int y);

    void setPixel(int x, int y, Color color);
    void addPixelColor(int x, int y, Color colorDifference);
    void subtractPixelColor(int x, int y, Color colorDifference);
    void drawRectangle(int x, int y, int w, int h, Color *pixelBuffer);

    void update();
    void clearLayer();
    bool isVisible() const {return visibleFlag;}
    void flipVisible();
    void setVisible(bool flag);

private:
    void addChunkToUpdate(const ChunkPtr &chunk);

// signals:
//     void fullLayerChanged(int selfIndex);
//     void rectLayerChanged(int selfIndex, const PIXELMAP::Rect &rect, Color *pixelBuffer);
//     void pixelChanged(int selfIndex, int x, int y);

private:
    std::vector<std::vector<ChunkPtr>> m_chunks;
    std::set<Chunk *> m_updatedChunks;
    int chunksInWidth;
    int chunksInHeight;
    const Rectangle m_rect;
    const Color defaultColor;

    QString m_name;
    bool visibleFlag = true;

public:
    COLOR::Blend *blend;
};

using LayerPtr = std::shared_ptr<Layer>;

}

#endif // LAYER_H
