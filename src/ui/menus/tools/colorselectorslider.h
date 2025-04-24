#ifndef COLORSELECTORSLIDER_H
#define COLORSELECTORSLIDER_H
#include <QWidget>

namespace PIPKA::UI {

class ColorSelectorSlider : public QWidget{
    Q_OBJECT
public:
    ColorSelectorSlider(
        float bottomLimit,
        float topLimit,
        QWidget* parent = nullptr);

    void setValue(float value);
signals:
    void valueChanged(float value);

protected:
    void initUI();
    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    void calculateValue();
    float mapPosition(float position) const;

private:
    const float m_bottomLimit;
    const float m_topLimit;
    float m_position;
    bool m_pressed;
    float m_value;



};

} // PIPKA

#endif //COLORSELECTORSLIDER_H
