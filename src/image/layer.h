#ifndef LAYER_H
#define LAYER_H

#include <cstdint>
#include <vector>
#include <QObject>


namespace PIPKA::IMAGE {

using Color = std::uint32_t; /// argb format, 8bit for each channel.

class Layer : public QObject
{
    Q_OBJECT

public:
    Layer(const int &index, const int &w, const int &h, const Color &color);
    // Layer(const Layer &layer);
    inline const int width()  {return w;};
    inline const int height() {return h;};
    inline std::vector<Color> pixels() {return m_pixels;};
    void testDifferentPixels();

signals:
    void layerChanged(
        int index);

private:
    std::vector<Color> m_pixels;
    const int w;
    const int h;
    int index;
};

}

#endif // LAYER_H
