#ifndef RAY_TRACER_SURFACE_HPP
#define RAY_TRACER_SURFACE_HPP

#include "utilities.hpp"
#include "vec3.hpp"

class Surface {
private:
    int index = 0;
    int width, height;
    const char* filename;
    uint8_t* pixels{};

public:
    Surface(int _width, int _height, const char* _filename);

    ~Surface();

    void write_color(Color pixel_color, int samples_per_pixel);

    void render();
};

#endif
