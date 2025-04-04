#ifndef RECTANGLE_H
#define RECTANGLE_H

struct Rectangle
{
    Rectangle(
        const int x, const int y,
        const int w, const int h) :
        x(x), y(y), w(w), h(h) { }

    bool contains(const int pointX, const int pointY) const
    {
        return pointX >= x && pointY >= y && pointX < x + w && pointY < y + h;
    }

    int maxX() const { return x + w; }
    int maxY() const { return y + h; }
    int bufferSize() const { return w * h; }
    int bufferIndex(const int pointX, const int pointY) const
    {
        return (pointX - x) + (pointY - y) * w;
    }

    const int x;
    const int y;
    const int w;
    const int h;
};
#endif //RECTANGLE_H
