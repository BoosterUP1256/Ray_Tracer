#include "imageIO.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include "external/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "external/stb_image_write.h"

void ImageIO::make_image(const char* filename, int width, int height, uint8_t* pixels)
{
    stbi_write_png(filename, width, height, 3, pixels, width*3);
}

unsigned char* ImageIO::load_image(const char* filename, int& width, int& height, int components_per_pixel)
{
    return stbi_load(filename, &width, &height, &components_per_pixel, components_per_pixel);
}
