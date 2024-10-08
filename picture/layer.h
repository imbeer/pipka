#ifndef LAYER_H
#define LAYER_H

#include <vector>

namespace PICTURE
{

struct pixelRGBA_f
{
    float r, g, b, a;
    pixelRGBA_f(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 1.0f)
        : r(red), g(green), b(blue), a(alpha) {}
};


class Layer
{

public:
    Layer(int w, int h);
    ~Layer();

    inline int convertCoordsInIndex(const int x, const int y) {return this->w * y + x;};
    pixelRGBA_f* pixels();
    pixelRGBA_f* pixel(const int x, const int y);
    void setPixel(const int x, const int y, const pixelRGBA_f pixel);

private:
    int w;
    int h;
    std::vector<pixelRGBA_f> buffer;
};

}

#endif // LAYER_H
