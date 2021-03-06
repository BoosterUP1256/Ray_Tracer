#ifndef RAY_TRACER_HITTABLE_HPP
#define RAY_TRACER_HITTABLE_HPP

#include "ray.hpp"
#include "aabb.hpp"

class Material;

struct Hit_record {
    Point3 p;
    Vec3 normal;
    shared_ptr<Material> mat_ptr;
    double t;
    double u;
    double v;
    bool front_face;

    inline void set_face_normal(const Ray& r, const Vec3& outward_normal)
    {
        front_face = dot(r.get_direction(), outward_normal)<0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const = 0;

    virtual bool bounding_box(double time0, double time1, Aabb& output_box) const = 0;
};

class Translate : public Hittable {
public:
    shared_ptr<Hittable> ptr;
    Vec3 offset;

    Translate(shared_ptr<Hittable> p, const Vec3& displacement)
            :ptr(std::move(p)), offset(displacement) { }

    bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const override;

    bool bounding_box(double time0, double time1, Aabb& output_box) const override;
};

class Rotate_y : public Hittable {
public:
    shared_ptr<Hittable> ptr;
    double sin_theta;
    double cos_theta;
    bool hasbox;
    Aabb bbox;

    Rotate_y(shared_ptr<Hittable> p, double angle);

    bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const override;

    bool bounding_box(double time0, double time1, Aabb& output_box) const override
    {
        output_box = bbox;
        return hasbox;
    }
};

#endif
