#include "hittable_list.hpp"

Hittable_list::Hittable_list(const shared_ptr<Hittable>& object)
{
    add(object);
}

void Hittable_list::clear()
{
    objects.clear();
}

void Hittable_list::add(const shared_ptr<Hittable>& object)
{
    objects.push_back(object);
}

bool Hittable_list::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const
{
    Hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for (const auto& object: objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

bool Hittable_list::bounding_box(double time0, double time1, Aabb& output_box) const
{
    if (objects.empty())
        return false;

    Aabb temp_box;
    bool first_box = true;

    for (const auto& object: objects) {
        if (!object->bounding_box(time0, time1, temp_box))
            return false;
        output_box = first_box ? temp_box : Aabb::surrounding_box(output_box, temp_box);
        first_box = false;
    }
    return true;
}
