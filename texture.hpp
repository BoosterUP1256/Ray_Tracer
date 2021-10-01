#ifndef RAY_TRACER_TEXTURE_HPP
#define RAY_TRACER_TEXTURE_HPP

#include "ray.hpp"
#include "perlin.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include "external/stb_image.h"

class Texture {
public:
    virtual Color value(double u, double v, const Point3& p) const = 0;
};

class Solid_color : public Texture {
private:
    Color color_value;

public:
    Solid_color() = default;

    explicit Solid_color(Color c)
            :color_value(c) { }

    Solid_color(double red, double green, double blue)
            :Solid_color(Color(red, green, blue)) { }

    Color value(double u, double v, const Vec3& p) const override
    {
        return color_value;
    }
};

class Checker_texture : public Texture {
public:
    shared_ptr<Texture> odd;
    shared_ptr<Texture> even;

    Checker_texture() = default;

    Checker_texture(shared_ptr<Texture> _even, shared_ptr<Texture> _odd)
            :even(std::move(_even)), odd(std::move(_odd)) { }

    Checker_texture(Color c1, Color c2)
            :even(make_shared<Solid_color>(c1)), odd(make_shared<Solid_color>(c2)) { }

    Color value(double u, double v, const Point3& p) const override
    {
        double sines = sin(10*p.x)*sin(10*p.y)*sin(10*p.z);
        if (sines<0)
            return odd->value(u, v, p);
        else
            return even->value(u, v, p);
    }
};

class Noise_texture : public Texture {
public:
    Perlin noise;
    double scale;

    Noise_texture() = default;

    explicit Noise_texture(double sc)
            :scale(sc) { }

    Color value(double u, double v, const Point3& p) const override
    {
        return Color(1, 1, 1)*0.5*(1+sin(scale*p.z+10*noise.turb(p)));
    }
};

class Image_texture : public Texture {
private:
    unsigned char* data;
    int width, height;
    int bytes_per_scanline;

public:
    const static int bytes_per_pixel = 3;

    Image_texture()
            :data(nullptr), width(0), height(0), bytes_per_scanline(0) { }

    Image_texture(const char* filename)
    {
        int components_per_pixel = bytes_per_pixel;

        data = stbi_load(filename, &width, &height, &components_per_pixel, components_per_pixel);

        if (!data) {
            std::cerr << "ERROR: Could not load texture image file ' " << filename << "'.\n";
            width = height = 0;
        }

        bytes_per_scanline = bytes_per_pixel*width;
    }

    ~Image_texture()
    {
        delete data;
    }

    Color value(double u, double v, const Vec3& p) const override
    {
        // If we have no texture data, then return solid cyan as a debugging aid.
        if (data==nullptr)
            return {0, 1, 1};

        // Clamp input texture coordinates to [0, 1] x [1, 0]
        u = clamp(u, 0.0, 1.0);
        v = 1.0-clamp(v, 0.0, 1.0);  // Flip V to image coordinates

        int i = static_cast<int>(u*width);
        int j = static_cast<int>(v*height);

        // Clamp integer mapping, since actual coordinates should be less than 1.0
        if (i>=width)
            i = width-1;
        if (j>=height)
            j = height-1;

        const double color_scale = 1.0/255.0;
        auto pixel = data+j*bytes_per_scanline+i*bytes_per_pixel;

        return {color_scale*pixel[0], color_scale*pixel[1], color_scale*pixel[2]};
    }
};

#endif
