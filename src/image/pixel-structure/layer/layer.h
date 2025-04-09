#ifndef LAYER_H
#define LAYER_H

namespace PIPKA::IMAGE
{

class Layer : public QObject
{
public:
    explicit Layer(const Rectangle &rectangle) : m_rect(rectangle) {};
    int width() const {return m_rect.w;}
    int height() const {return m_rect.h;}

    virtual Color getColor(int x, int y) = 0;
    virtual void setPixel(int x, int y, Color color) = 0;
    virtual void addPixelColor(int x, int y, Color colorDifference) = 0;
    virtual void subtractPixelColor(int x, int y, Color colorDifference) = 0;
    virtual void drawRectangle(const Rectangle &rectangle, Color *pixelBuffer)
    {
        for (int x = rectangle.x; x < rectangle.w + rectangle.x; ++x) {
            for (int y = rectangle.y; y < rectangle.h + rectangle.y; ++y) {
                setPixel(x, y, pixelBuffer[rectangle.bufferIndex(x, y)]);
            }
        }
    }
    virtual void clearLayer() = 0;


public:
    const Rectangle m_rect;
};

using LayerPtr = std::shared_ptr<Layer>;

}


#endif //LAYER_H
