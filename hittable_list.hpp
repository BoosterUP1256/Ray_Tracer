#ifndef RAY_TRACER_HITTABLE_LIST_HPP
#define RAY_TRACER_HITTABLE_LIST_HPP

#include "hittable.hpp"
#include "aabb.hpp"

#include  <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class Hittable_list : public Hittable {
public:
    std::vector<shared_ptr<Hittable>> objects;

    Hittable_list() = default;

    explicit Hittable_list(const shared_ptr<Hittable>& object);

    void clear();

    void add(const shared_ptr<Hittable>& object);

    bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const override;

    bool bounding_box(double time0, double time1, Aabb& output_box) const override;
};

#endif