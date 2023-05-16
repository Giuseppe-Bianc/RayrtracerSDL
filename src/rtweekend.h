#pragma once
#include "headers.h"
#include "Ray.h"
#include "Vec3.h"

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = glm::pi<double>();

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}


inline double random_double() {
    static std::uniform_real_distribution<double> distribution;
    static std::mt19937 generator;
    return distribution(generator);
}
inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}