#ifndef COLORSELECTORSQUARE_H
#define COLORSELECTORSQUARE_H
#include <QWidget>

#include "../../../control/controller.h"

namespace PIPKA::UI
{
class ColorSelectorSquare : public QWidget {
    Q_OBJECT

public:
    explicit ColorSelectorSquare(
        QWidget *parent = nullptr);

    void setHue(float hue);

    void mousePressEvent  (QMouseEvent  *event) override;
    void mouseReleaseEvent  (QMouseEvent  *event) override;
    void mouseMoveEvent     (QMouseEvent  *event) override;
    void paintEvent         (QPaintEvent *event)  override;

    void calculateColorOnClick(double x, double y);

signals:
    void colorSelected(float saturation, float value);

private:
    QPointF m_lastPos{0, 0};
    float m_hue = 0.0f;
    bool m_pressed = false;
};

}

#endif //COLORSELECTORSQUARE_H
