#ifndef COLOR_H_
#define COLOR_H_

#include "vec3.h"

#include <iostream>

using color = vec3;

inline double linear_to_gamma(double linear_component) {
    return sqrt(linear_component);
}

void write_color(std::ostream& out, color pixel_color, int sample_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples
    auto scale = 1.0 / sample_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Linear to gamma transform
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const interval intensity(0.000, 0.999);
    out << static_cast<int>(256 * intensity.clamp(r)) << ' '
    << static_cast<int>(256 * intensity.clamp(g)) << ' '
    << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

#endif