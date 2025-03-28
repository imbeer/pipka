#ifndef COLOR_H
#define COLOR_H

#include <algorithm>
#include <cstdint>


namespace PIPKA::IMAGE {

using Color = std::uint32_t;
using Channel = std::uint8_t;

namespace COLOR {

class HSVAColor
{
public:
    HSVAColor(float hue, float saturation, float value, float alpha);
    explicit HSVAColor(Color rgbColor);
    void fromRGB(Color rgbColor);
    [[nodiscard]] Color toRGB() const;

public:
    /// 0.0 <= num <= 1.0
    float hue {};
    float saturation {};
    float value {};
    float alpha {};
};

[[nodiscard]] inline Color makeColor(
    const Channel &alpha,
    const Channel &red,
    const Channel &green,
    const Channel &blue) {
    const Color result = (alpha << 24) | (red << 16) | (green << 8) | blue;
    return result;
};

inline void setAlpha(Color &color, const Channel &newAlpha) { color &= 0x00FFFFFF; color |= (newAlpha << 24); };
inline void setRed  (Color &color, const Channel &newRed  ) { color &= 0xFF00FFFF; color |= (newRed   << 16); };
inline void setGreen(Color &color, const Channel &newGreen) { color &= 0xFFFF00FF; color |= (newGreen <<  8); };
inline void setBlue (Color &color, const Channel &newBlue ) { color &= 0xFFFFFF00; color |= newBlue ; };

[[nodiscard]] inline Channel alpha(const Color &color) {return (color >> 24) & 0xFF;};
[[nodiscard]] inline Channel red  (const Color &color) {return (color >> 16) & 0xFF;};
[[nodiscard]] inline Channel green(const Color &color) {return (color >>  8) & 0xFF;};
[[nodiscard]] inline Channel blue (const Color &color) {return color & 0xFF;};

[[nodiscard]] inline float   hexToFloat(const Channel &channel) {return static_cast<float>(channel) / 0xFF;};
[[nodiscard]] inline Channel floatToHex(const float &color) {return std::clamp(static_cast<int>(color * 0xFF), 0, 0xFF);};

}

}

#endif // COLOR_H
