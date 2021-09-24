#ifndef RAY_TRACER_TEXTURE_HPP
#define RAY_TRACER_TEXTURE_HPP

#include <utility>

#include "ray.hpp"

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

#endif
