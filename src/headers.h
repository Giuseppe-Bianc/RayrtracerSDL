#pragma once

#define GLM_FORCE_SILENT_WARNINGS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_WIN32
#define GLM_FORCE_SIZE_T_LENGTH
#define GLM_FORCE_PURE
#define GLM_FORCE_INLINE
#define GLM_FORCE_EXPLICIT_CTOR
#define GLM_FORCE_CXX17
#define GLM_FORCE_UNRESTRICTED_GENTYPE
#define GLM_FORCE_PRECISION_HIGHP_DOUBLE
#define GLM_FORCE_PRECISION_HIGHP_INT
#define GLM_FORCE_PRECISION_HIGHP_FLOAT
//#define GLM_FORCE_MESSAGES
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/random.hpp>
#include <string_view>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

#define CAST_ST(x) static_cast<std::size_t>((x))
#define CAST_UC(x) static_cast<unsigned char>((x))
#define CAST_U8(x) static_cast<Uint8>((x))
#define CAST_I(x) static_cast<int>((x))
#define CAST_ULLI(x) static_cast<long long int>((x))
#define CAST_D(x) static_cast<double>((x))
#define PRINT(p, ...)  std::cout << std::fixed << std::setprecision(p) << __VA_ARGS__ << std::endl;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define SDL_COLORU8(r, g, b, a) { CAST_U8(r), CAST_U8(g), CAST_U8(b), CAST_U8(a) }
#define SDL_COLOR(r, g, b, a) { r,g,b,a }
#else
#define SDL_COLORU8(r, g, b, a) { CAST_U8(b), CAST_U8(g), CAST_U8(r), CAST_U8(a) }
#define SDL_COLOR(r, g, b, a) { b, g, r, a }
#endif

using ddvector = std::vector<std::vector<double>>;
namespace SDLRT {
	static constexpr bool FWDTF = true;
	static constexpr bool BCKTF = false;
	static constexpr double MAX_COLOR = 255.0;
	static constexpr double NO_COLOR = 0.0;
	static constexpr double EPSILON = 1e-22;
	// Dimensioni della finestra
	static constexpr int w = 800;
	static constexpr int h = 400;
	static constexpr int nCh = 3;
	static constexpr std::size_t dataSize = CAST_ST(w * h * nCh);
	static constexpr double scale = 255.99999;
	static constexpr std::string_view windowTitle = "Ray Tracer";
	static constexpr std::string_view errorMessage = "Errore durante l'inizializzazione di SDL: ";
	static constexpr std::string_view createWindowErrorMessage = "Errore durante la creazione della finestra: ";
	static constexpr std::string_view createRendererErrorMessage = "Errore durante la creazione dell' render: ";
}
