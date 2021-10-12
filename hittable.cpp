#include "hittable.hpp"

#include <utility>

bool Translate::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const
{
    Ray moved_r(r.get_origin()-offset, r.get_direction(), r.get_time());
    if (!ptr->hit(moved_r, t_min, t_max, rec))
        return false;

    rec.p += offset;
    rec.set_face_normal(moved_r, rec.normal);

    return true;
}

bool Translate::bounding_box(double time0, double time1, Aabb& output_box) const
{
    if (!ptr->bounding_box(time0, time1, output_box))
        return false;

    output_box = Aabb(output_box.get_min()+offset, output_box.get_max()+offset);

    return true;
}

Rotate_y::Rotate_y(shared_ptr<Hittable> p, double angle)
        :ptr(std::move(p))
{
    double radians = degrees_to_radians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    hasbox = ptr->bounding_box(0, 1, bbox);

    Point3 min(infinity, infinity, infinity);
    Point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i<2; i++) {
        for (int j = 0; j<2; j++) {
            for (int k = 0; k<2; k++) {
                double x = i*bbox.get_max().x+(1-i)*bbox.get_min().x;
                double y = j*bbox.get_max().y+(1-j)*bbox.get_min().y;
                double z = k*bbox.get_max().z+(1-k)*bbox.get_min().z;

                double newx = cos_theta*x+sin_theta*z;
                double newz = -sin_theta*x+cos_theta*z;

                Vec3 tester(newx, y, newz);

                for (int c = 0; c<3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }
    bbox = Aabb(min, max);
}

bool Rotate_y::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const
{
    Point3 origin = r.get_origin();
    Vec3 direction = r.get_direction();

    origin.x = cos_theta*r.get_origin().x-sin_theta*r.get_origin().z;
    origin.z = sin_theta*r.get_origin().x+cos_theta*r.get_origin().z;

    direction.x = cos_theta*r.get_direction().x-sin_theta*r.get_direction().z;
    direction.z = sin_theta*r.get_direction().x+cos_theta*r.get_direction().z;

    Ray rotated_r(origin, direction, r.get_time());

    if (!ptr->hit(rotated_r, t_min, t_max, rec))
        return false;

    Point3 p = rec.p;
    Vec3 normal = rec.normal;

    p.x = cos_theta*rec.p.x+sin_theta*rec.p.z;
    p.z = -sin_theta*rec.p.x+cos_theta*rec.p.z;

    normal.x = cos_theta*rec.normal.x+sin_theta*rec.normal.z;
    normal.z = -sin_theta*rec.normal.x+cos_theta*rec.normal.z;

    rec.p = p;
    rec.set_face_normal(rotated_r, normal);

    return true;
}
