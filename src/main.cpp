#include "rstb_image.h"
#include "sdltemplate.h"
#include "rtweekend.h"
#include "Color.h"
#include "Hittable_list.h"
#include "Sphere.h"
#include "Camera.h"

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);
    if (world.hit(r, 0.001, infinity, rec)) {
        point3 target = rec.p + random_in_hemisphere(rec.normal);
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
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
    camera cam;

    // Render

    std::vector<unsigned char> data(SDLRT::dataSize);
    sdltemplate::sdl("Ray Tracer", SDLRT::w, SDLRT::h);
    sdltemplate::loop();
    for (int j = SDLRT::h -1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < SDLRT::w; ++i) {
            color pcolor{ 0, 0, 0 };
            for (int s = 0; s < SDLRT::samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (SDLRT::w - 1);
                auto v = (j + random_double()) / (SDLRT::h - 1);
                ray r = cam.get_ray(u, v);
                pcolor += ray_color(r, world, SDLRT::max_depth);
            }
            std::size_t index = SDLRT::nCh * CAST_ST(j * SDLRT::w + i);
            write_color(data, pcolor, index, SDLRT::samples_per_pixel);
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

