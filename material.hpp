#ifndef RAY_TRACER_MATERIAL_HPP
#define RAY_TRACER_MATERIAL_HPP

#include <utility>

#include "utilities.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "texture.hpp"

struct Hit_record;

class Material {
public:
    virtual bool scatter(const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
    shared_ptr<Texture> albedo;

    explicit Lambertian(const Color& a)
            :albedo(make_shared<Solid_color>(a)) { }

    explicit Lambertian(shared_ptr<Texture> a)
            :albedo(std::move(a)) { }

    bool scatter(const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered) const override
    {
        Vec3 scatter_direction = rec.normal+random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = Ray(rec.p, scatter_direction, r_in.get_time());
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }
};

class Metal : public Material {
public:
    Color albedo;
    double fuzz;

    Metal(const Color& a, double f)
            :albedo(a), fuzz(f<1 ? f : 1) { }

    bool scatter(const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered) const override
    {
        Vec3 reflected = reflect(unit_vector(r_in.get_direction()), rec.normal);
        scattered = Ray(rec.p, reflected+fuzz*random_in_unit_sphere(), r_in.get_time());
        attenuation = albedo;
        return (dot(scattered.get_direction(), rec.normal)>0);
    }
};

class Dielectric : public Material {
private:
    static double reflecatnce(double cosine, double ref_idx)
    {
        // Use Schlick's approximation for reflectance.
        double r0 = (1-ref_idx)/(1+ref_idx);
        r0 = r0*r0;
        return r0+(1-r0)*pow((1-cosine), 5);
    }

public:
    double ir; // Index of Refraction

    explicit Dielectric(double index_of_refraction)
            :ir(index_of_refraction) { }

    bool scatter(const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered) const override
    {
        attenuation = Color(1.0, 1.0, 1.0);
        double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

        Vec3 unit_direction = unit_vector(r_in.get_direction());
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0-cos_theta*cos_theta);

        bool cannot_refract = refraction_ratio*sin_theta>1.0;
        Vec3 direction;
        if (cannot_refract || reflecatnce(cos_theta, refraction_ratio)>random_double())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, refraction_ratio);

        scattered = Ray(rec.p, direction, r_in.get_time());
        return true;
    }
};

#endif
