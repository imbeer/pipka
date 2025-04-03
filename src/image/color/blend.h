#ifndef BLEND_H
#define BLEND_H

#include "color.h"

namespace PIPKA::IMAGE::COLOR {

class Blend {
public:
    virtual ~Blend() = default;

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

class ReplaceBlend final : public Blend{
public:
    Color blend(const Color &background, const Color &foreground) override;

protected:
    Channel channel(const float &bgChannel, const float &bgAlpha, const float &fgChannel,
        const float &fgAlpha) override;
};

class NormalBlend final : public Blend{
public:
     Channel channel(
        const float &bgChannel, const float &bgAlpha,
        const float &fgChannel, const float &fgAlpha) override;
};

class MultiplyBlend final : public Blend{
public:
    Channel channel(
        const float &bgChannel, const float &bgAlpha,
        const float &fgChannel, const float &fgAlpha) override;
};

class ScreenBlend final : public Blend{
public:
    Channel channel(
        const float &bgChannel, const float &bgAlpha,
        const float &fgChannel, const float &fgAlpha) override;
};

class OverlayBlend final : public Blend{
public:
    Channel channel(
        const float &bgChannel, const float &bgAlpha,
        const float &fgChannel, const float &fgAlpha) override;
};

}

#endif // BLEND_H
