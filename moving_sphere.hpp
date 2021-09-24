#ifndef RAY_TRACER_MOVING_SPHERE_HPP
#define RAY_TRACER_MOVING_SPHERE_HPP

#include "utilities.hpp"
#include "hittable.hpp"
#include "vec3.hpp"
#include "aabb.hpp"

class Moving_sphere : public Hittable {
public:
    Point3 center0, center1;
    double time0, time1;
    double radius;
    shared_ptr<Material> mat_ptr;

    Moving_sphere() = default;

    Moving_sphere(Point3 cen0, Point3 cen1, double _time0, double _time1, double r, shared_ptr<Material> m);

    bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const override;

    bool bounding_box(double _time0, double _time1, Aabb& output_box) const override;

    Point3 center(double time) const;
};

#endif
