#include "color.h"
#include <algorithm>

namespace PIPKA::IMAGE {

Color blend(const Color &background, const Color &foreground, const BlendMode &mode) {
    switch(mode) {
    case BlendMode::NORMAL:
        return normalBlend(background, foreground);
    default:
        return foreground;
    }
}

Color normalBlend(const Color &background, const Color &foreground)
{
    Channel fgAlpha = COLOR::alpha(foreground);
    Channel fgRed   = COLOR::red  (foreground);
    Channel fgGreen = COLOR::green(foreground);
    Channel fgBlue  = COLOR::blue (foreground);

    Channel bgAlpha = COLOR::alpha(background);
    Channel bgRed   = COLOR::red  (background);
    Channel bgGreen = COLOR::green(background);
    Channel bgBlue  = COLOR::blue (background);

    // if (fgAlpha == 0xFF || bgAlpha == 0x00) return foreground;
    // if (fgAlpha == 0x00) return background;

    int alphaSum = bgAlpha + fgAlpha;

    Channel alpha = std::clamp(alphaSum, 0, 0xFF);
    Channel red   = std::clamp((bgRed   * bgAlpha + fgRed   * fgAlpha) / alphaSum, 0, 0xFF);
    Channel green = std::clamp((bgGreen * bgAlpha + fgGreen * fgAlpha) / alphaSum, 0, 0xFF);
    Channel blue  = std::clamp((bgBlue  * bgAlpha + fgBlue  * fgAlpha) / alphaSum, 0, 0xFF);

    return COLOR::makeColor(alpha, red, green, blue);
}

}
