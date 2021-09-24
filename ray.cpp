#include "ray.hpp"

Ray::Ray(const Point3& origin, const Vec3& direction, double time = 0.0)
        :orig(origin), dir(direction), tm(time) { }

Point3 Ray::get_origin() const
{
    return orig;
}

Vec3 Ray::get_direction() const
{
    return dir;
}

double Ray::get_time() const
{
    return tm;
}

Point3 Ray::at(double t) const
{
    return orig+t*dir;
}
