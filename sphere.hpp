#ifndef RAY_TRACER_SPHERE_HPP
#define RAY_TRACER_SPHERE_HPP

#include "hittable.hpp"
#include "vec3.hpp"
#include "aabb.hpp"

class Sphere : public Hittable {
private:
    static void get_sphere_uv(const Point3& p, double& u, double& v);

public:
    Point3 center;
    double radius;
    shared_ptr<Material> mat_ptr;

    Sphere() = default;

    Sphere(Point3 cen, double r, shared_ptr<Material> m);

    bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const override;

    bool bounding_box(double time0, double time1, Aabb& output_box) const override;
};

#endif
