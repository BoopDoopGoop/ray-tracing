#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "vec3.h"

using color = vec3;

void write_color(std::ostream &out, color pixel, int samples_per_pixel) {
    auto r = pixel.x();
    auto g = pixel.y();
    auto b = pixel.z();

    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    static const interval intensity(0.000, 0.999);
    out << static_cast<int>(256*intensity.clamp(r)) << ' '
        << static_cast<int>(256*intensity.clamp(g)) << ' '
        << static_cast<int>(256*intensity.clamp(b)) << '\n';
}

#endif