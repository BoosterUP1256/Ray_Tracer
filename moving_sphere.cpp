#include "moving_sphere.hpp"

Moving_sphere::Moving_sphere(Point3 cen0, Point3 cen1, double _time0, double _time1, double r, shared_ptr<Material> m)
        :center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat_ptr(m) { }

bool Moving_sphere::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const
{
    Vec3 oc = r.get_origin()-center(r.get_time());
    double a = r.get_direction().length_squared();
    double half_b = dot(oc, r.get_direction());
    double c = oc.length_squared()-radius*radius;

    double discriminant = half_b*half_b-a*c;
    if (discriminant<0)
        return false;
    double sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    double root = (-half_b-sqrtd)/a;
    if (root<t_min || t_max<root) {
        root = (-half_b+sqrtd)/a;
        if (root<t_min || t_max<root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outward_normal = (rec.p-center(r.get_time()))/radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

Point3 Moving_sphere::center(double time) const
{
    return center0+((time-time0)/(time1-time0))*(center1-center0);
}

bool Moving_sphere::bounding_box(double _time0, double _time1, Aabb& output_box) const
{
    Aabb box0(center(_time0)-Vec3(radius, radius, radius), center(_time0)+Vec3(radius, radius, radius));
    Aabb box1(center(_time1)-Vec3(radius, radius, radius), center(_time1)+Vec3(radius, radius, radius));
    output_box = Aabb::surrounding_box(box0, box1);
    return true;
}
