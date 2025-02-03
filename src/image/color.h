#ifndef COLOR_H
#define COLOR_H

#include <cstdint>


namespace PIPKA::IMAGE {

using Color = std::uint32_t;

Color blendColors(const Color &background, const Color &foreground);

void setAlpha(Color& color, uint8_t newAlpha);

inline uint8_t getAlpha(Color& color) {return (color >> 24) & 0xFF;};

}

#endif // COLOR_H
