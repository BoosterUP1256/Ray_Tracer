#ifndef RAY_TRACER_AABB_HPP
#define RAY_TRACER_AABB_HPP

#include "vec3.hpp"
#include "ray.hpp"

class Aabb {
private:
    Point3 minimum;
    Point3 maximum;

public:
    Aabb() = default;

    Aabb(const Point3& a, const Point3& b);

    Point3 get_min();

    Point3 get_max();

    bool hit(const Ray& r, double t_min, double t_max) const;

    static Aabb surrounding_box(Aabb box0, Aabb box1);
};

#endif