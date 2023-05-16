#include "rstb_image.h"
#include "sdltemplate.h"
#include "rtweekend.h"
#include "Color.h"
#include "Hittable_list.h"
#include "Material.h"
#include "Sphere.h"
#include "Camera.h"


hittable_list random_scene() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return color(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    // World
    hittable_list world = random_scene();

    // Camera

    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, SDLRT::aspect_ratio, aperture, dist_to_focus);

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

