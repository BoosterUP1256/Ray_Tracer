#ifndef RAY_TRACER_SURFACE_HPP
#define RAY_TRACER_SURFACE_HPP

#include "utilities.hpp"
#include "vec3.hpp"

#include <vector>
#include <SDL2/SDL.h>

class Surface {
private:
    int index = 0;
    int width, height;
    const char* filename;
    uint8_t* pixels{};
    SDL_Renderer* renderer;
    SDL_Window* window;
    struct Pixel {
        int x;
        int y;
        Color color;
    };
    std::vector<Pixel> pixel_buffer;

public:
    Surface(int _width, int _height, const char* _filename);

    ~Surface();

    void write_color(Color pixel_color, int samples_per_pixel);

    void render();
};

#endif
