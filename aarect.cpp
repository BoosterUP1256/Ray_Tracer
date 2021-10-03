#include "aarect.hpp"

#include <utility>

Xy_rect::Xy_rect(double _x0, double _x1, double _y0, double _y1, double _k, shared_ptr<Material> mat)
        :x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(std::move(mat)) { }

bool Xy_rect::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const
{
    double t = (k-r.get_origin().z)/r.get_direction().z;
    if (t<t_min || t>t_max)
        return false;
    double x = r.get_origin().x+t*r.get_direction().x;
    double y = r.get_origin().y+t*r.get_direction().y;
    if (x<x0 || x>x1 || y<y0 || y>y1)
        return false;
    rec.u = (x-x0)/(x1-x0);
    rec.v = (y-y0)/(y1-y0);
    rec.t = t;
    Vec3 outward_normal = Vec3(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.at(t);
    return true;
}

bool Xy_rect::bounding_box(double time0, double time1, Aabb& output_box) const
{
    // The bounding box must have non-zero width in each dimension, so pad the z
    // dimension a small amount.
    output_box = Aabb(Point3(x0, y0, k-0.0001), Point3(x1, y1, k+0.0001));
    return true;
}

Xz_rect::Xz_rect(double _x0, double _x1, double _z0, double _z1, double _k, shared_ptr<Material> mat)
        :x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(std::move(mat)) { }

bool Xz_rect::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const
{
    double t = (k-r.get_origin().y)/r.get_direction().y;
    if (t<t_min || t>t_max)
        return false;
    double x = r.get_origin().x+t*r.get_direction().x;
    double z = r.get_origin().z+t*r.get_direction().z;
    if (x<x0 || x>x1 || z<z0 || z>z1)
        return false;
    rec.u = (x-x0)/(x1-x0);
    rec.v = (z-z0)/(z1-z0);
    rec.t = t;
    Vec3 outward_normal = Vec3(0, 1, 0);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.at(t);
    return true;
}

bool Xz_rect::bounding_box(double time0, double time1, Aabb& output_box) const
{
    // The bounding box must have non-zero width in each dimension, so pad the Y
    // dimension a small amount.
    output_box = Aabb(Point3(x0, k-0.0001, z0), Point3(x1, k+0.0001, z1));
    return true;
}

Yz_rect::Yz_rect(double _y0, double _y1, double _z0, double _z1, double _k, shared_ptr<Material> mat)
        :y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(std::move(mat)) { }

bool Yz_rect::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const
{
    double t = (k-r.get_origin().x)/r.get_direction().x;
    if (t<t_min || t>t_max)
        return false;
    double y = r.get_origin().y+t*r.get_direction().y;
    double z = r.get_origin().z+t*r.get_direction().z;
    if (y<y0 || y>y1 || z<z0 || z>z1)
        return false;
    rec.u = (y-y0)/(y1-y0);
    rec.v = (z-z0)/(z1-z0);
    rec.t = t;
    Vec3 outward_normal = Vec3(1, 0, 0);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.at(t);
    return true;
}

bool Yz_rect::bounding_box(double time0, double time1, Aabb& output_box) const
{
    // The bounding box must have a non-zero width in each dimension, so pad the X
    // dimension a small amount.
    output_box = Aabb(Point3(k-0.0001, y0, z0), Point3(k+0.0001, y1, z1));
    return true;
}
