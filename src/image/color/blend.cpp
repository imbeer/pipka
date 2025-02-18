#include "blend.h"

namespace PIPKA::IMAGE::COLOR {

Color Blend::blend(const Color &background, const Color &foreground)
{
    const float fgAlpha { hexToFloat(COLOR::alpha(foreground)) };
    const float fgRed   { hexToFloat(red  (foreground)) * fgAlpha };
    const float fgGreen { hexToFloat(green(foreground)) * fgAlpha };
    const float fgBlue  { hexToFloat(blue (foreground)) * fgAlpha };

    const float bgAlpha { hexToFloat(COLOR::alpha(background)) };
    const float bgRed   { hexToFloat(red  (background)) * bgAlpha };
    const float bgGreen { hexToFloat(green(background)) * bgAlpha };
    const float bgBlue  { hexToFloat(blue (background)) * bgAlpha };

    const Channel alpha { this->alpha(bgAlpha, fgAlpha) };
    const Channel red   { channel(bgRed,   bgAlpha, fgRed,   fgAlpha) };
    const Channel green { channel(bgGreen, bgAlpha, fgGreen, fgAlpha) };
    const Channel blue  { channel(bgBlue,  bgAlpha, fgBlue,  fgAlpha) };

    return makeColor(alpha, red, green, blue);
}

Color ReplaceBlend::blend(const Color &background, const Color &foreground)
{
    return foreground; // maybe make a copy?
}

Channel NormalBlend::channel(
    const float &bgChannel, const float &bgAlpha,
    const float &fgChannel, const float &fgAlpha)
{
    return floatToHex(fgChannel + bgChannel * (1 - fgAlpha));
}

Channel MultiplyBlend::channel(
    const float &bgChannel, const float &bgAlpha,
    const float &fgChannel, const float &fgAlpha)
{
    return floatToHex(fgChannel * bgChannel + fgChannel * (1 - bgAlpha) + bgChannel *  (1 - fgAlpha));
}

Channel ScreenBlend::channel(
    const float &bgChannel, const float &bgAlpha,
    const float &fgChannel, const float &fgAlpha)
{
    return floatToHex(fgChannel + bgChannel - (fgChannel * bgChannel));
}

Channel OverlayBlend::channel(
    const float &bgChannel, const float &bgAlpha,
    const float &fgChannel, const float &fgAlpha)
{
    return floatToHex(fgChannel + bgChannel - (fgChannel * bgChannel ));
}

}
