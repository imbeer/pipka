#ifndef RECTANGLE_H
#define RECTANGLE_H

struct Rectangle
{
    Rectangle(
        const int x, const int y,
        const int w, const int h,
        const Rectangle &biggerRectangle) :
        x(x), y(y), w(w), h(h), vertices(computeVertices(biggerRectangle))
    { }

    Rectangle(
        const int x, const int y,
        const int w, const int h) :
        x(x), y(y), w(w), h(h),
        vertices({
            // Positions    // Texture Coords
            -1.0f, -1.0f, 1.0,  0.0f, 0.0f,
             1.0f, -1.0f, 1.0,  1.0f, 0.0f,
            -1.0f,  1.0f, 1.0,  0.0f, 1.0f,
             1.0f,  1.0f, 1.0,  1.0f, 1.0f,
        })
    { }

    [[nodiscard]] bool contains(const int pointX, const int pointY) const
    {
        return pointX >= x && pointY >= y && pointX < x + w && pointY < y + h;
    }

    [[nodiscard]] int maxX() const { return x + w; }
    [[nodiscard]] int maxY() const { return y + h; }
    [[nodiscard]] int bufferSize() const { return w * h; }
    [[nodiscard]] int bufferIndex(const int pointX, const int pointY) const
    {
        return (pointX - x) + (pointY - y) * w;
    }

    [[nodiscard]] std::array<float, 20> computeVertices(const Rectangle &biggerRectangle) const
    {
        const float left   = 2.0f * (x - biggerRectangle.x) / biggerRectangle.w - 1.0f;
        const float right  = 2.0f * ((x + w) - biggerRectangle.x) / biggerRectangle.w - 1.0f;
        const float bottom = 2.0f * (y - biggerRectangle.y) / biggerRectangle.h - 1.0f;
        const float top    = 2.0f * ((y + h) - biggerRectangle.y) / biggerRectangle.h - 1.0f;

        return {
            // Positions        // Texture Coords
            left,  bottom, 1.0f,  0.0f, 0.0f,
            right, bottom, 1.0f,  1.0f, 0.0f,
            left,  top,    1.0f,  0.0f, 1.0f,
            right, top,    1.0f,  1.0f, 1.0f,
        };
    }

    const int x;
    const int y;
    const int w;
    const int h;

    std::array<float, 20> vertices;
};
#endif //RECTANGLE_H
