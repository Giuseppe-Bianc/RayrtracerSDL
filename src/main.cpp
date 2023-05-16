#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include "sdltemplate.h"
#include "Ray.h"
#include "Color.h"
#include "Vec3.h"

color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
   
    sdltemplate::sdl("Ray Tracer", SDLRT::w, SDLRT::h);
    sdltemplate::loop();

    std::vector<unsigned char> data(SDLRT::dataSize);
    for (int j = SDLRT::h -1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < SDLRT::w; ++i) {
            color pcolor{ CAST_D(i) / (SDLRT::w - 1), CAST_D(j) / (SDLRT::h - 1), 0.25 };
            std::size_t index = SDLRT::nCh * CAST_ST(j * SDLRT::w + i);
            write_color(data, pcolor, index);
            sdltemplate::setDrawColor(sdltemplate::createColor(data.at(index), data.at(index+1), data.at(index+2), 255));
            sdltemplate::drawPoint(i, SDLRT::h-j);
        }
    }
    std::cerr << "\nDone.\n";
    stbi_flip_vertically_on_write(1);
    stbi_write_png("one.png", SDLRT::w, SDLRT::h, SDLRT::nCh, data.data(), SDLRT::w * SDLRT::nCh);

    while (sdltemplate::running) {
        sdltemplate::loop();
    }
    return 0;
}

