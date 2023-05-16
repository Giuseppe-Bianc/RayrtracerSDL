#pragma once
#include "Vec3.h"

void write_color(std::ostream& out, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << CAST_I(255.999 * pixel_color.x()) << ' '
        << CAST_I(255.999 * pixel_color.y()) << ' '
        << CAST_I(255.999 * pixel_color.z()) << '\n';
}