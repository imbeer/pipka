#ifndef BLEND_H
#define BLEND_H

#include "color.h"

namespace PIPKA::IMAGE::COLOR {

class Blend {
public:
    virtual Color blend(const Color &background, const Color &foreground);

protected:
    virtual Channel channel(
        const float &bgChannel, const float &bgAlpha,
        const float &fgChannel, const float &fgAlpha) = 0;

    virtual Channel alpha(const float &bgAlpha, const float &fgAlpha)
    {
        return floatToHex(fgAlpha + bgAlpha - fgAlpha * bgAlpha);
    }
};

class ReplaceBlend : public Blend{
public:
    virtual Color blend(const Color &background, const Color &foreground) override;
};

class NormalBlend : public Blend{
public:
     virtual Channel channel(
        const float &bgChannel, const float &bgAlpha,
        const float &fgChannel, const float &fgAlpha) override;
};

class MultiplyBlend : public Blend{
public:
    virtual Channel channel(
        const float &bgChannel, const float &bgAlpha,
        const float &fgChannel, const float &fgAlpha) override;
};

class ScreenBlend : public Blend{
public:
    virtual Channel channel(
        const float &bgChannel, const float &bgAlpha,
        const float &fgChannel, const float &fgAlpha) override;
};

class OverlayBlend : public Blend{
public:
    virtual Channel channel(
        const float &bgChannel, const float &bgAlpha,
        const float &fgChannel, const float &fgAlpha) override;
};

}

#endif // BLEND_H
