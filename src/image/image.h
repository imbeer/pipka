#ifndef IMAGE_H
#define IMAGE_H

#include "layer.h"
#include <vector>

namespace PIPKA::IMAGE {

class Image : public QObject
{
    Q_OBJECT
public:
    Image(
        const int &w,
        const int &h);

    [[nodiscard]] int width() const {return w;};
    [[nodiscard]] int height() const {return h;};
    [[nodiscard]] float ratio() const {return static_cast<float>(w) / h;};
    [[nodiscard]] int layerSize() const {return m_layers.size();};
    std::vector<std::shared_ptr<Layer>> layers() {return m_layers;};
    std::vector<Color> pixels() {return m_mergedImage;};
    void insertLayer(const int &index);
    void pushBackLayer();
    QImage toQImage() const;

private:
    Color renderPixel(const int &index) const;
    void mergePixel(const int &layerIndex, const int &x, const int &y);
    void mergeAllPixels(const int &layerIndex);

signals:
    void layerAdded(int index);
    void pixelChanged(const int &x, const int &y);
    void allPixelsChanged();

private:
    const int w;
    const int h;

    std::vector<std::shared_ptr<Layer>> m_layers;
    std::vector<Color> m_mergedImage;
};

}

#endif // IMAGE_H
