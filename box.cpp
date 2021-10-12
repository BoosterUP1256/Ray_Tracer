#include "box.hpp"

Box::Box(const Point3& p0, const Point3& p1, shared_ptr<Material> ptr)
{
    box_min = p0;
    box_max = p1;

    sides.add(make_shared<Xy_rect>(p0.x, p1.x, p0.y, p1.y, p1.z, ptr));
    sides.add(make_shared<Xy_rect>(p0.x, p1.x, p0.y, p1.y, p0.z, ptr));

    sides.add(make_shared<Xz_rect>(p0.x, p1.x, p0.z, p1.z, p1.y, ptr));
    sides.add(make_shared<Xz_rect>(p0.x, p1.x, p0.z, p1.z, p0.y, ptr));

    sides.add(make_shared<Yz_rect>(p0.y, p1.y, p0.z, p1.z, p1.x, ptr));
    sides.add(make_shared<Yz_rect>(p0.y, p1.y, p0.z, p1.z, p0.x, ptr));
}

bool Box::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const
{
    return sides.hit(r, t_min, t_max, rec);
}

bool Box::bounding_box(double time0, double time1, Aabb& output_box) const
{
    output_box = Aabb(box_min, box_max);
    return true;
}
