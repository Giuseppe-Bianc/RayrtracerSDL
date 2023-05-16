#pragma once
#include "Ray.h"

void write_color(std::vector<unsigned char>& data, color pixel_color, std::size_t index) {
    // Write the translated [0,255] value of each color component.
    data.at(index)     = CAST_UC(255.999 * pixel_color.x());
    data.at(index + 1) = CAST_UC(255.999 * pixel_color.y());
    data.at(index + 2) = CAST_UC(255.999 * pixel_color.z());
}