#ifndef RAY_TRACER_BVH_HPP
#define RAY_TRACER_BVH_HPP

#include "utilities.hpp"
#include "hittable_list.hpp"

class Bvh_node : public Hittable {
public:
    shared_ptr<Hittable> left;
    shared_ptr<Hittable> right;
    Aabb box;

    Bvh_node();

    Bvh_node(const Hittable_list& list, double time0, double time1);

    Bvh_node(const std::vector<shared_ptr<Hittable>>& src_objects, size_t start, size_t end, double time0,
            double time1);

    bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const override;

    bool bounding_box(double time0, double time1, Aabb& output_box) const override;
};

inline bool box_compare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b, int axis)
{
    Aabb box_a;
    Aabb box_b;

    if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
        std::cerr << "No bounding box in Bvh_node constructor" << std::endl;
    return box_a.get_min()[axis]<box_b.get_min()[axis];
}

// TODO: refacter to be static methods (maybe do this to other classes as well like Vec3)
bool box_x_compare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b)
{
    return box_compare(a, b, 1);
}

bool box_y_compare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b)
{
    return box_compare(a, b, 1);
}

bool box_z_compare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b)
{
    return box_compare(a, b, 2);
}

#endif
