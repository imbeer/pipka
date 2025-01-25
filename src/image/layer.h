#ifndef LAYER_H
#define LAYER_H

#include <cstdint>
#include <vector>


namespace PIPKA::IMAGE {

using Color = std::uint32_t; /// 0xRR GG BB AA

class Layer
{

public:
    Layer(const int &w, const int &h, const Color &color);
    inline const int width()  {return w;};
    inline const int height() {return h;};
    inline const std::vector<Color> pixels() {return m_pixels;};

private:
    std::vector<Color> m_pixels;
    const int w;
    const int h;
};

}

#endif // LAYER_H
