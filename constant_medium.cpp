#include "constant_medium.hpp"

Constant_medium::Constant_medium(shared_ptr<Hittable> b, double d, const shared_ptr<Texture>& a)
        :boundary(std::move(b)), neg_inv_density(-1/d), phase_function(make_shared<Isotropic>(a)) { }

Constant_medium::Constant_medium(shared_ptr<Hittable> b, double d, Color c)
        :boundary(std::move(b)), neg_inv_density(-1/d), phase_function(make_shared<Isotropic>(c)) { }

bool Constant_medium::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const
{
    // Print occasional samples when debugging. To enable, set enableDebug true.
    const bool enable_debug = false;
    const bool debugging = enable_debug && random_double()<0.00001;

    Hit_record rec1, rec2;

    if (!boundary->hit(r, -infinity, infinity, rec1))
        return false;

    if (!boundary->hit(r, rec1.t+0.0001, infinity, rec2))
        return false;

    if (debugging)
        std::cerr << "\nt_min=" << rec1.t << ", t_max=" << rec2.t << std::endl;

    if (rec1.t<t_min)
        rec1.t = t_min;

    if (rec2.t>t_max)
        rec2.t = t_max;

    if (rec1.t>=rec2.t)
        return false;

    if (rec1.t<0)
        rec1.t = 0;

    const double ray_length = r.get_direction().length();
    const double distance_inside_boundary = (rec2.t-rec1.t)*ray_length;
    const double hit_distance = neg_inv_density*log(random_double());

    if (hit_distance>distance_inside_boundary)
        return false;

    rec.t = rec1.t+hit_distance/ray_length;
    rec.p = r.at(rec.t);

    if (debugging) {
        std::cerr << "hit_distance = " << hit_distance << std::endl
                  << "rec.t = " << rec.t << std::endl
                  << "rec.p = " << rec.p << std::endl;
    }

    rec.normal = Vec3(1, 0, 0);  // arbitrary
    rec.front_face = true;                 // also arbitrary
    rec.mat_ptr = phase_function;

    return true;
}

bool Constant_medium::bounding_box(double time0, double time1, Aabb& output_box) const
{
    return boundary->bounding_box(time0, time1, output_box);
}
