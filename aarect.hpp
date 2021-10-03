#ifndef RAY_TRACER_AARECT_HPP
#define RAY_TRACER_AARECT_HPP

#include "utilities.hpp"
#include "hittable.hpp"

class Xy_rect : public Hittable {
public:
    shared_ptr<Material> mp;
    double x0, x1, y0, y1, k;

    Xy_rect() = default;

    Xy_rect(double _x0, double _x1, double _y0, double _y1, double _k, shared_ptr<Material> mat);

    bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const override;

    bool bounding_box(double time0, double time1, Aabb& output_box) const override;
};

class Xz_rect : public Hittable {
public:
    shared_ptr<Material> mp;
    double x0, x1, z0, z1, k;

    Xz_rect() = default;

    Xz_rect(double _x0, double _x1, double _z0, double _z1, double _k, shared_ptr<Material> mat);

    bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const override;

    bool bounding_box(double time0, double time1, Aabb& output_box) const override;
};

class Yz_rect : public Hittable {
public:
    shared_ptr<Material> mp;
    double y0, y1, z0, z1, k;

    Yz_rect() = default;

    Yz_rect(double _y0, double _y1, double _z0, double _z1, double _k, shared_ptr<Material> mat);

    bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const override;

    bool bounding_box(double time0, double time1, Aabb& output_box) const override;
};

#endif
