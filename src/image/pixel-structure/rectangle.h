#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <array>
#include <QVector3D>
#include <QDebug>

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
    [[nodiscard]] bool contains(const QVector3D &point) const
    {
        return point.x() >= x && point.y() >= y && point.x() < x + w && point.y() < y + h;
    }

    [[nodiscard]] float distance(const QVector3D &point) const
    {
        if (contains(point))
            return -1.0f;

        const float halfWidth = w * 0.5f;
        const float halfHeight = h * 0.5f;

        const float centerX = x + halfWidth;
        const float centerY = y + halfHeight;

        const float distanceX = std::abs(point.x() - centerX) - halfWidth;
        const float distanceY = std::abs(point.y() - centerY) - halfHeight;

        if (distanceX > 0.0f && distanceY > 0.0f) {
            return std::sqrt(distanceX * distanceX + distanceY * distanceY);
        } else {
            return std::max(distanceX, distanceY);
        }
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
        const float left   = 2.0f * static_cast<float>(x - biggerRectangle.x) / biggerRectangle.w - 1.0f;
        const float right  = 2.0f * static_cast<float>((x + w) - biggerRectangle.x) / biggerRectangle.w - 1.0f;
        const float bottom = 2.0f * static_cast<float>(y - biggerRectangle.y) / biggerRectangle.h - 1.0f;
        const float top    = 2.0f * static_cast<float>((y + h) - biggerRectangle.y) / biggerRectangle.h - 1.0f;

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
