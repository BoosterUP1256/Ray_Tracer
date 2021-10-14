#include "constant_medium.hpp"

Constant_medium::Constant_medium(shared_ptr<Hittable> b, double d, const shared_ptr<Texture>& a)
        :boundary(std::move(b)), neg_inv_density(-1/d), phase_function(make_shared<Isotropic>(a)) { }

Constant_medium::Constant_medium(shared_ptr<Hittable> b, double d, Color c)
        :boundary(std::move(b)), neg_inv_density(-1/d), phase_function(make_shared<Isotropic>(c)) { }

bool Constant_medium::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const
{
    return false;
}

bool Constant_medium::bounding_box(double time0, double time1, Aabb& output_box) const
{
    return boundary->bounding_box(time0, time1, output_box);
}
