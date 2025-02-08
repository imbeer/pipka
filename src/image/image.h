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

    inline const int width() {return w;};
    inline const int height() {return h;};
    inline const float ratio() {return static_cast<float>(w) / h;};
    inline const int layerSize() {return m_layers.size();};
    inline std::vector<std::shared_ptr<Layer>> layers() {return m_layers;};

public:
    void insertLayer(const int &index);
    void pushBackLayer();
    QImage toQImage();

signals:
    void layerAdded(int index);

private:
    const int w;
    const int h;

    std::vector<std::shared_ptr<Layer>> m_layers;
};

}

#endif // IMAGE_H
