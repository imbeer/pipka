#include "colorselectorwidget.h"

#include <QVBoxLayout>
#include <utility>

#include "../../../control/repository/brushrepository.h"

namespace PIPKA::UI {

ColorSelectorWidget::ColorSelectorWidget(
    const std::shared_ptr<CONTROL::Controller> &controller,
    QWidget *parent) :
    QWidget(parent), m_controller(controller)
{
    initUI();
    updateColor();
}

void ColorSelectorWidget::initUI()
{
    setFixedSize(QSize(256, 280));
    this->setLayout(new QVBoxLayout());
    const auto layout = this->layout();
    layout->setSpacing(5);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignCenter | Qt::AlignAbsolute);
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

    connect(
        CONTROL::TOOLS::BrushRepository::instance(), &CONTROL::TOOLS::BrushRepository::brushSelected,
        this, &ColorSelectorWidget::brushChanged);
}

void ColorSelectorWidget::updateColor() const
{
    const IMAGE::Color color = m_color.toRGB();
    CONTROL::TOOLS::BrushRepository::instance()->activeBrush()->setColor(color);
}

void ColorSelectorWidget::brushChanged()
{
    m_color = IMAGE::COLOR::HSVAColor(CONTROL::TOOLS::BrushRepository::instance()->activeBrush()->color());
    m_gradientSquare->setColor(m_color);
    m_alphaSlider->setValue(m_color.alpha);
    m_hueSlider->setValue(m_color.hue / 360);
}

void ColorSelectorWidget::saturationAndValueChanged(float saturation, float value)
{
    m_color.saturation = saturation;
    m_color.value = value;
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
