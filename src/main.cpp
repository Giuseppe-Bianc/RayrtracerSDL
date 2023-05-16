#include "rstb_image.h"
#include "sdltemplate.h"
#include "rtweekend.h"
#include "Color.h"
#include "Hittable_list.h"
#include "Sphere.h"

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = SDLRT::aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render

    std::vector<unsigned char> data(SDLRT::dataSize);
    sdltemplate::sdl("Ray Tracer", SDLRT::w, SDLRT::h);
    sdltemplate::loop();
    for (int j = SDLRT::h -1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < SDLRT::w; ++i) {
            auto u = double(i) / (SDLRT::w - 1);
            auto v = double(j) / (SDLRT::h - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pcolor = ray_color(r, world);
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

