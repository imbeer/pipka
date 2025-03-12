#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <QObject>
#include "color/color.h"
#include "color/blend.h"
#include "pixel/pixelmap.h"

namespace PIPKA::IMAGE {

class Layer : public QObject
{
    Q_OBJECT

public:
    Layer(const int &index, const int &w, const int &h, const Color &color);

    [[nodiscard]] int width() const {return w;}
    [[nodiscard]] int height() const {return h;}
    std::vector<Color> pixels() {return m_pixels;}
    QString name() {return m_name;}
    void setName(const QString &name) {m_name = name;}

    [[nodiscard]] Color getColor(int x, int y) const;
    [[nodiscard]] Color getColor(int index) const;
    void testDifferentPixels();
    void drawPixel(int x, int y, Color color);
    void addPixelColor(int x, int y, Color colorDifference);
    void subtractPixelColor(int x, int y, Color colorDifference);
    void update(const PIXELMAP::Rect &rect);
    void clearLayer();
    bool isVisible() const {return visibleFlag;}
    void flipVisible();
    void setVisible(bool flag);
signals:
    void fullLayerChanged(int selfIndex);
    void rectLayerChanged(int selfIndex, const PIXELMAP::Rect &rect);
    void pixelChanged(int selfIndex, int x, int y);

private:
    std::vector<Color> m_pixels;
    const int w;
    const int h;
    const Color defaultColor;
    int m_index;
    QString m_name;
    bool visibleFlag = true;

public:
    std::shared_ptr<COLOR::Blend> blend;
};

}

#endif // LAYER_H
