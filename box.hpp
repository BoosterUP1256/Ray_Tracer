#ifndef RAY_TRACER_BOX_HPP
#define RAY_TRACER_BOX_HPP

#include "utilities.hpp"

#include "aarect.hpp"
#include "hittable_list.hpp"

class Box : public Hittable {
public:
    Point3 box_min;
    Point3 box_max;
    Hittable_list sides;

    Box() = default;

    Box(const Point3& p0, const Point3& p1, shared_ptr<Material> ptr);

    bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const override;

    bool bounding_box(double time0, double time1, Aabb& output_box) const override;
};

#endif
