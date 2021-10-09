#include "surface.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "external/stb_image_write.h"

Surface::Surface(int _width, int _height, const char* _filename)
        :width(_width), height(_height), filename(_filename)
{
    pixels = new uint8_t[width*height*3];
}

Surface::~Surface()
{
    delete[] pixels;
}

void Surface::write_color(Color pixel_color, int samples_per_pixel)
{
    double r = pixel_color.x;
    double g = pixel_color.y;
    double b = pixel_color.z;

    // Divide the color by the number of samples.
    double scale = 1.0/samples_per_pixel;
    r = sqrt(scale*r);
    g = sqrt(scale*g);
    b = sqrt(scale*b);

    // Write the translated [0, 255] value of each color component.
    pixels[index++] = static_cast<int>(256*clamp(r, 0.0, 0.999));
    pixels[index++] = static_cast<int>(256*clamp(g, 0.0, 0.999));
    pixels[index++] = static_cast<int>(256*clamp(b, 0.0, 0.999));
}

void Surface::render()
{
    stbi_write_png(filename, width, height, 3, pixels, width*3);
}
