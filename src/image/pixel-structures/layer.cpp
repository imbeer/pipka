#include "layer.h"

#include <qdebug.h>
#include "../../control/repositories/blendrepository.h"

namespace PIPKA::IMAGE {

Layer::Layer(
    const int index,
    const Color color,
    const Rectangle &rectangle) :
    m_rect(rectangle),
    defaultColor(color)
{
    splitToChunks();
    blend = CONTROL::TOOLS::BlendRepository::instance()->getBlend<COLOR::NormalBlend>();
    m_name = "Layer " + QString::number(index);
}

void Layer::splitToChunks()
{
    const int numMaxSizedChunksInWidth = width() / Chunk::MAX_SIDE;
    const int lastChunkInWidth = width() % Chunk::MAX_SIDE;
    chunksInWidth = numMaxSizedChunksInWidth + (lastChunkInWidth > 0 ? 1 : 0);

    const int numMaxSizedChunksInHeight = height() / Chunk::MAX_SIDE;
    const int lastChunkInHeight = height() % Chunk::MAX_SIDE;
    chunksInHeight = numMaxSizedChunksInHeight + (lastChunkInHeight > 0 ? 1 : 0);

    for (int yInd = 0; yInd <= numMaxSizedChunksInHeight; yInd++) {
        auto chunkRow = std::vector<ChunkPtr>();
        for (int xInd = 0; xInd <= numMaxSizedChunksInWidth; xInd++) {

            const int chunkX = xInd * Chunk::MAX_SIDE;
            const int chunkY = yInd * Chunk::MAX_SIDE;
            int chunkWidth = Chunk::MAX_SIDE;
            int chunkHeight = Chunk::MAX_SIDE;
            if (xInd == numMaxSizedChunksInWidth) {
                chunkWidth = lastChunkInWidth;
            }
            if (yInd == numMaxSizedChunksInHeight) {
                chunkHeight = lastChunkInHeight;
            }

            if (chunkHeight == 0 || chunkWidth == 0)
                continue;

            auto chunk = std::make_shared<Chunk>(
                chunkX, chunkY,
                chunkWidth, chunkHeight,
                xInd, yInd,
                defaultColor, m_rect);
            chunkRow.push_back(chunk);
        }
        if (!chunkRow.empty()) {
            m_chunks.push_back(chunkRow);
        }
    }
}

ChunkPtr Layer::getChunkOfPoint(const int pointX, const int pointY)
{
    const int xInd = pointX / Chunk::MAX_SIDE;
    const int yInd = pointY / Chunk::MAX_SIDE;

    return m_chunks.at(yInd).at(xInd);
}

ChunkPtr Layer::getChunk(const int xInd, const int yInd)
{
    return m_chunks.at(yInd).at(xInd);
}

Color Layer::getColor(const int x, const int y)
{
    if (!m_rect.contains(x, y)) return 0;
    return getChunkOfPoint(x, y)->getPixel(x, y);
}

void Layer::setPixel(const int x, const int y, const Color color)
{
    if (!m_rect.contains(x, y)) return;
    const auto chunk = getChunkOfPoint(x, y);
    chunk->setPixel(x, y, color);
    addChunkToUpdate(chunk);
}

void Layer::addPixelColor(const int x, const int y, const Color colorDifference)
{
    if (!m_rect.contains(x, y)) return;
    const auto chunk = getChunkOfPoint(x, y);
    chunk->setPixel(x, y, chunk->getPixel(x, y) + colorDifference);
    addChunkToUpdate(chunk);
}

void Layer::subtractPixelColor(const int x, const int y, const Color colorDifference)
{
    if (!m_rect.contains(x, y)) return;
    const auto chunk = getChunkOfPoint(x, y);
    chunk->setPixel(x, y, chunk->getPixel(x, y) - colorDifference);
    addChunkToUpdate(chunk);
}

void Layer::drawRectangle(const int x, const int y, const int w, const int h, Color *pixelBuffer)
{
    for (int xInd = 0; xInd < w; ++xInd) {
        for (int yInd = 0; yInd < h; ++yInd) {
            setPixel(x + xInd, y + yInd, pixelBuffer[xInd + yInd * w]);
        }
    }
}

void Layer::update()
{
    // qDebug() << "Layer::update" << m_updatedChunks.size();
    for (const auto chunkPtr : m_updatedChunks) {
        chunkPtr->update();
    }
    m_updatedChunks.clear();
}

void Layer::clearLayer()
{
    for (auto &chunkRow : m_chunks) {
        for (auto &chunk : chunkRow) {
            chunk->clear();
            addChunkToUpdate(chunk);
        }
    }
    update();
}

void Layer::flipVisible()
{
    visibleFlag = !visibleFlag;
}

void Layer::setVisible(const bool flag)
{
    visibleFlag = flag;
}

void Layer::addChunkToUpdate(const ChunkPtr &chunk)
{
    Chunk *chunkPtr = chunk.get();
    if (!m_updatedChunks.contains(chunkPtr)) {
        m_updatedChunks.insert(chunkPtr);
    }
}

}
