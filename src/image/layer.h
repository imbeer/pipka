#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <QObject>
#include "color.h"

namespace PIPKA::IMAGE {

class Layer : public QObject
{
    Q_OBJECT

public:
    Layer(const int &index, const int &w, const int &h, const Color &color);
    // Layer(const Layer &layer);
    inline const int width()  {return w;};
    inline const int height() {return h;};
    inline std::vector<Color> pixels() {return m_pixels;};
    Color getColor(const int &x, const int &y);
    void testDifferentPixels();
    void drawPixel(const int &x, const int &y, const Color &color);
    void clearLayer();

    void update();

signals:
    void layerChanged(
        int index);

private:
    std::vector<Color> m_pixels;
    const int w;
    const int h;
    const Color defaultColor;
    int m_index;
};

}

#endif // LAYER_H
