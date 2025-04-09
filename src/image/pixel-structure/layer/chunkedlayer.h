#ifndef CHUNKED_LAYER_H
#define CHUNKED_LAYER_H
#include <set>
#include <vector>

#include "../chunk.h"
#include "layer.h"
#include "../../color/color.h"
#include "../pixelmap.h"

namespace PIPKA::IMAGE {

class ChunkedLayer final : public Layer
{
    Q_OBJECT
public:
    explicit ChunkedLayer(
        const Rectangle &rectangle);

private:
    void splitToChunks();

public:

    ChunkPtr getChunkOfPoint(int pointX, int pointY);
    ChunkPtr getChunk(int xInd, int yInd);
    const std::vector<std::vector<ChunkPtr>> &chunks() const { return m_chunks; }
    Color getColor(int x, int y) override;
    void setPixel(int x, int y, Color color) override;
    void addPixelColor(int x, int y, Color colorDifference) override;
    void subtractPixelColor(int x, int y, Color colorDifference) override;

    void update();
    void clearLayer() override;

private:
    void addChunkToUpdate(const ChunkPtr &chunk);

signals:
    void updated();

private:
    std::vector<std::vector<ChunkPtr>> m_chunks;
    std::set<Chunk *> m_updatedChunks;
    int chunksInWidth;
    int chunksInHeight;
};

using ChunkedLayerPtr = std::shared_ptr<ChunkedLayer>;

}

#endif // CHUNKED_LAYER_H
