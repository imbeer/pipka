#include "color.h"
#include <algorithm>

namespace PIPKA::IMAGE {

Color blendColors(const Color &background, const Color &foreground)
{
    uint8_t bg_alpha = (background >> 24) & 0xFF;
    uint8_t bg_red = (background >> 16) & 0xFF;
    uint8_t bg_green = (background >> 8) & 0xFF;
    uint8_t bg_blue = background & 0xFF;

    // Extract the alpha, red, green, blue channels for foreground
    uint8_t fg_alpha = (foreground >> 24) & 0xFF;
    uint8_t fg_red = (foreground >> 16) & 0xFF;
    uint8_t fg_green = (foreground >> 8) & 0xFF;
    uint8_t fg_blue = foreground & 0xFF;

    int alpha_sum = bg_alpha + fg_alpha;

    int result_red = (bg_red * bg_alpha + fg_red * fg_alpha) / alpha_sum;
    int result_green = (bg_green * bg_alpha + fg_green * fg_alpha) / alpha_sum;
    int result_blue = (bg_blue * bg_alpha + fg_blue * fg_alpha) / alpha_sum;

    result_red = std::min(255, std::max(0, result_red));
    result_green = std::min(255, std::max(0, result_green));
    result_blue = std::min(255, std::max(0, result_blue));
    alpha_sum = std::min(255, std::max(0, alpha_sum));

    Color result = (alpha_sum << 24) | (result_red << 16) | (result_green << 8) | result_blue;

    return result;
}

void setAlpha(Color& color, uint8_t newAlpha)
{
    color &= 0x00FFFFFF;
    color |= (newAlpha << 24);
}

}
