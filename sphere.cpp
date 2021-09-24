#include "sphere.hpp"

void Sphere::get_sphere_uv(const Point3& p, double& u, double& v)
{
    // p: a given point on the sphere of radius one, centered at the origin.
    // U: returned value [0, 1] of angle around teh Y axis from x=-1.
    // v: returned value [0, 1] of angle from y=-1 to y=+1.
    //      <1 0 0> yields <0.50 0.50>      <-1 0 0> yields <0.00 0.50>
    //      <0 1 0> yields <0.50 1.00>      <0 -1 0> yields <0.50 0.00>
    //      <0 0 1> yields <0.25 0.50>      <0 0 -1> yields <0.75 0.50>

    double theta = acos(-p.y);
    double phi = atan2(-p.z, p.x)+pi;

    u = phi/(2*pi);
    v = theta/pi;
}

Sphere::Sphere(Point3 cen, double r, shared_ptr<Material> m)
        :center(cen), radius(r), mat_ptr(std::move(m)) { }

bool Sphere::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const
{
    Vec3 oc = r.get_origin()-center;
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
    Vec3 outward_normal = (rec.p-center)/radius;
    rec.set_face_normal(r, outward_normal);
    get_sphere_uv(outward_normal, rec.u, rec.v);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool Sphere::bounding_box(double time0, double time1, Aabb& output_box) const
{
    output_box = Aabb(center-Vec3(radius, radius, radius), center+Vec3(radius, radius, radius));
    return true;
}
