#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include "sdltemplate.h"
#include "Color.h"
#include "Vec3.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
   
    sdltemplate::sdl("Ray Tracer", SDLRT::w, SDLRT::h);
    sdltemplate::loop();

    std::vector<unsigned char> data(SDLRT::dataSize);
    for (int j = SDLRT::h -1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < SDLRT::w; ++i) {
            color pcolor(double(i) / (SDLRT::w - 1), double(j) / (SDLRT::h - 1), 0.25);

            auto ir = CAST_UC(SDLRT::scale * pcolor[0]);
            auto ig = CAST_UC(SDLRT::scale * pcolor[1]);
            auto ib = CAST_UC(SDLRT::scale * pcolor[2]);
            
            std::size_t index = SDLRT::nCh * CAST_ST(j * SDLRT::w + i);
            data.at(index) = ir;
            data.at(index + 1) = ig;
            data.at(index + 2) = ib;
            sdltemplate::setDrawColor(sdltemplate::createColor(ir, ig, ib, 255));
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

