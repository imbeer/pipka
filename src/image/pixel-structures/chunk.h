#ifndef CHUNK_H
#define CHUNK_H
#include <QObject>
#include <vector>
#include <QDebug>

#include "rectangle.h"
#include "../color/color.h"

namespace PIPKA::IMAGE
{

class Chunk : public QObject{
    Q_OBJECT
public:
    Chunk(
        int x, int y,
        int w, int h,
        int xInd, int yInd,
        Color initColor, const Rectangle &layerRect);
    /// point x, point y are coordinates in whole layer.
    Color getPixel(int pointX, int pointY) const;
    void setPixel(int pointX, int pointY, Color color);
    void clear();
    const void *data() const { return m_pixelBuffer.data(); }
    void update()
    {
        // qDebug() << "updating chunk" << m_xInd << m_yInd ;
        emit updated(m_xInd, m_yInd);
    }

signals:
    void updated(int xInd, int yInd);

public:
    static constexpr int MAX_SIDE = 64;

    const Rectangle rect;
    const Color initColor;

private:
    std::vector<Color> m_pixelBuffer;
    const int m_xInd;
    const int m_yInd;
};

using ChunkPtr = std::shared_ptr<Chunk>;

}

#endif //CHUNK_H
