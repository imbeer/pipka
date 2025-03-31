#ifndef COLORSELECTORWIDGET_H
#define COLORSELECTORWIDGET_H
#include <QWidget>

#include "colorselectorslider.h"
#include "colorselectorsquare.h"
#include "../../../control/controller.h"
#include "../../../image/color/color.h"

namespace PIPKA::UI {

class ColorSelectorWidget : public QWidget {
public:
    explicit ColorSelectorWidget(
        std::shared_ptr<CONTROL::Controller> controller,
        QWidget *parent = nullptr);

    void initUI();

private:
    void updateColor() const;

    void saturationAndValueChanged(float saturation, float value);
    void alphaChanged(float alpha);
    void hueChanged(float hue);

private:
    IMAGE::COLOR::HSVAColor m_color{0, 0, 0, 0};
    std::shared_ptr<CONTROL::Controller> m_controller;
    ColorSelectorSquare *m_gradientSquare = nullptr;
    ColorSelectorSlider *m_alphaSlider = nullptr;
    ColorSelectorSlider *m_hueSlider = nullptr;
};

}

#endif //COLORSELECTORWIDGET_H
