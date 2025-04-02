#include "colorselectorwidget.h"

#include <QVBoxLayout>

namespace PIPKA::UI {

ColorSelectorWidget::ColorSelectorWidget(
    std::shared_ptr<CONTROL::Controller> controller,
    QWidget *parent) :
    QWidget(parent), m_controller(controller)
{
    initUI();
}

void ColorSelectorWidget::initUI()
{
    this->setLayout(new QVBoxLayout());
    const auto layout = this->layout();
    layout->setSpacing(5);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignCenter);
    m_gradientSquare = new ColorSelectorSquare(this);
    m_alphaSlider = new ColorSelectorSlider(0, 1, this);
    m_hueSlider = new ColorSelectorSlider(0, 1, this);
    layout->addWidget(m_gradientSquare);
    layout->addWidget(m_alphaSlider);
    layout->addWidget(m_hueSlider);

    connect(
        m_gradientSquare, &ColorSelectorSquare::colorSelected,
        this, &ColorSelectorWidget::saturationAndValueChanged);

    connect(
        m_alphaSlider, &ColorSelectorSlider::valueChanged,
        this, &ColorSelectorWidget::alphaChanged);

    connect(
        m_hueSlider, &ColorSelectorSlider::valueChanged,
        this, &ColorSelectorWidget::hueChanged);
}

void ColorSelectorWidget::updateColor() const
{
    const IMAGE::Color color = m_color.toRGB();
    // qDebug() << QString::number(color, 16);
    m_controller->setColor(color);
}

void ColorSelectorWidget::saturationAndValueChanged(float saturation, float value)
{
    m_color.saturation = saturation;
    m_color.value = value;
    // qDebug() << "saturation: " << m_color.saturation << ", value: " << m_color.value;
    updateColor();
}

void ColorSelectorWidget::alphaChanged(float alpha)
{
    m_color.alpha = alpha;
    updateColor();
}

void ColorSelectorWidget::hueChanged(float hue)
{
    m_gradientSquare->setHue(hue);
    m_color.hue = std::clamp(hue * 360, 0.0f, 359.0f);
    updateColor();
}
}
