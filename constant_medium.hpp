#ifndef RAY_TRACER_CONSTANT_MEDIUM_HPP
#define RAY_TRACER_CONSTANT_MEDIUM_HPP

#include "hittable.hpp"
#include "material.hpp"
#include "texture.hpp"

class Constant_medium : public Hittable {
public:
    shared_ptr<Hittable> boundary;
    shared_ptr<Material> phase_function;
    double neg_inv_density;

    Constant_medium(shared_ptr<Hittable> b, double d, const shared_ptr<Texture>& a);

    Constant_medium(shared_ptr<Hittable> b, double d, Color c);

    bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const override;

    bool bounding_box(double time0, double time1, Aabb& output_box) const override;
};

#endif
