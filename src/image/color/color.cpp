#include "color.h"

namespace PIPKA::IMAGE {

Color blend(const Color &background, const Color &foreground, const BlendMode &mode) {
    switch(mode) {
    case BlendMode::REPLACE:
        return replace(background, foreground);
    case BlendMode::NORMAL:
        return normal(background, foreground);
    default:
        return foreground;
    }
}

Color replace(const Color &background, const Color &foreground)
{
    return foreground;
}

Color normal(const Color &background, const Color &foreground)
{
    float fgAlpha = COLOR::hexToFloat(COLOR::alpha(foreground));
    float fgRed   = COLOR::hexToFloat(COLOR::red  (foreground)) * fgAlpha;
    float fgGreen = COLOR::hexToFloat(COLOR::green(foreground)) * fgAlpha;
    float fgBlue  = COLOR::hexToFloat(COLOR::blue (foreground)) * fgAlpha;

    float bgAlpha = COLOR::hexToFloat(COLOR::alpha(background));
    float bgRed   = COLOR::hexToFloat(COLOR::red  (background)) * bgAlpha;
    float bgGreen = COLOR::hexToFloat(COLOR::green(background)) * bgAlpha;
    float bgBlue  = COLOR::hexToFloat(COLOR::blue (background)) * bgAlpha;

    Channel alpha = COLOR::floatToHex(fgAlpha + bgAlpha - (fgAlpha * bgAlpha));
    Channel red   = COLOR::floatToHex(fgRed   + bgRed   * (1 - fgAlpha));
    Channel green = COLOR::floatToHex(fgGreen + bgGreen * (1 - fgAlpha));
    Channel blue  = COLOR::floatToHex(fgBlue  + bgBlue  * (1 - fgAlpha));

    return COLOR::makeColor(alpha, red, green, blue);
}

}
