#ifndef RAY_TRACER_IMAGEIO_HPP
#define RAY_TRACER_IMAGEIO_HPP

#include <cstdint>

class ImageIO {
public:
    static void make_image(const char* filename, int width, int height, uint8_t* pixels);

    static unsigned char* load_image(const char* filename, int width, int height, int components_per_pixel);
};

#endif
