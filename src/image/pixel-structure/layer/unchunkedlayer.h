#ifndef UNCHUNKEDLAYER_H
#define UNCHUNKEDLAYER_H
#include "chunkedlayer.h"
#include "layer.h"

#include "../../color/blend.h"
#include "../buffer/layerversionbuffer.h"

namespace PIPKA::IMAGE
{

class UnchunkedLayer final : public Layer {
    Q_OBJECT
public:
    UnchunkedLayer(
        int index,
        Color color,
        const Rectangle &rectangle);

    QString name() {return m_name;}
    void setName(const QString &name) {m_name = name;}

    Color getColor(int x, int y) override;
    void setPixel(int x, int y, Color color) override;
    void addPixelColor(int x, int y, Color colorDifference) override;
    void subtractPixelColor(int x, int y, Color colorDifference) override;
    void addRectangle(const Rectangle &rectangle, const Color *pixelBuffer);
    void subtractRectangle(const Rectangle &rectangle, const Color *pixelBuffer);
    std::vector<Color> data() const {return m_pixelBuffer; }
    std::shared_ptr<BUFFER::LayerVersionBuffer> versions() { return m_versions; }

    bool isVisible() const {return visibleFlag;}
    void flipVisible();
    void setVisible(bool flag);

    void clearLayer() override;

signals:
    void pixelUpdated(int x, int y);
    void rectangleUpdated(Rectangle rectangle);

private:
    QString m_name;
    bool visibleFlag = true;
    const Color defaultColor;
    std::vector<Color> m_pixelBuffer;
    std::shared_ptr<BUFFER::LayerVersionBuffer> m_versions;

public:
    COLOR::Blend *blend;
};

using UnchunkedLayerPtr = std::shared_ptr<UnchunkedLayer>;


}

#endif //UNCHUNKEDLAYER_H
