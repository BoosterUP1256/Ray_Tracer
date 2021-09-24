#include "aabb.hpp"

Aabb::Aabb(const Point3& a, const Point3& b)
{
    minimum = a;
    maximum = b;
}

Point3 Aabb::get_min()
{
    return minimum;
}

Point3 Aabb::get_max()
{
    return maximum;
}

bool Aabb::hit(const Ray& r, double t_min, double t_max) const
{
    for (int a = 0; a<3; a++) {
        double invD = 1.0f/r.get_direction()[a];
        double t0 = (minimum[a]-r.get_origin()[a])*invD;
        double t1 = (maximum[a]-r.get_origin()[a])*invD;
        if (invD<0.0f)
            std::swap(t0, t1);
        t_min = t0>t_min ? t0 : t_min;
        t_max = t1<t_max ? t1 : t_max;
        if (t_max<=t_min)
            return false;
    }
    return true;
}

Aabb Aabb::surrounding_box(Aabb box0, Aabb box1)
{
    Point3 small(fmin(box0.get_min().x, box1.get_min().x), fmin(box0.get_min().y, box1.get_min().y),
            fmin(box0.get_min().z, box1.get_min().z));
    Point3 big(fmax(box0.get_max().x, box1.get_max().x), fmax(box0.get_max().y, box1.get_max().y),
            fmax(box0.get_max().z, box1.get_max().z));
    return {small, big};
}
