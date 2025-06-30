#include "color.h"

#include <cmath>

namespace PIPKA::IMAGE::COLOR
{

HSVAColor::HSVAColor(const float hue, const float saturation, const float value, const float alpha):
    hue(hue), saturation(saturation), value(value), alpha(alpha)
{ }

HSVAColor::HSVAColor(const Color rgbColor)
{
    fromRGB(rgbColor);
}

// todo: needs testing
void HSVAColor::fromRGB(Color rgbColor)
{
    const float alpha = hexToFloat(COLOR::alpha(rgbColor));
    const float red   = hexToFloat(COLOR::red  (rgbColor));
    const float green = hexToFloat(COLOR::green(rgbColor));
    const float blue  = hexToFloat(COLOR::blue (rgbColor));

    const float max = std::max(std::max(red, green), blue);
    const float min = std::min(std::min(red, green), blue);
    const float delta = max - min;

    this->hue = 0.0f;
    this->saturation = (max == 0) ? 0.0f : delta / max;
    this->value = static_cast<float>(max);
    this->alpha = static_cast<float>(alpha);

    if (delta > 0) {
        if (max == red) {
            this->hue = 60.0f * std::fmod(((green - blue) / delta), 6.0f);
        } else if (max == green) {
            this->hue = 60.0f * (((blue - red) / delta) + 2.0f);
        } else if (max == blue) {
            this->hue = 60.0f * (((red - green) / delta) + 4.0f);
        }
        if (this->hue < 0) this->hue += 360.0f;
    }
}

// todo: needs testing
Color HSVAColor::toRGB() const
{
    const float c = value * saturation;
    const auto x = static_cast<float>(c * (1 - std::abs(std::fmod(hue / 60.0, 2) - 1)));
    const float m = value - c;
    float redF = 0, greenF = 0, blueF = 0;

    if (hue >= 0 && hue < 60) {
        redF = c, greenF = x, blueF = 0;
    } else if (hue >= 60 && hue < 120) {
        redF = x, greenF = c, blueF = 0;
    } else if (hue >= 120 && hue < 180) {
        redF = 0, greenF = c, blueF = x;
    } else if (hue >= 180 && hue < 240) {
        redF = 0, greenF = x, blueF = c;
    } else if (hue >= 240 && hue < 300) {
        redF = x, greenF = 0, blueF = c;
    } else if (hue >= 300 && hue < 360) {
        redF = c, greenF = 0, blueF = x;
    }

    const Channel red = floatToHex(redF + m);
    const Channel green = floatToHex(greenF + m);
    const Channel blue = floatToHex(blueF + m);
    const Channel alpha = floatToHex(this->alpha);
    return makeColor(alpha, red, green, blue);
}

}
