#ifndef RAY_TRACER_RAY_HPP
#define RAY_TRACER_RAY_HPP

#include "vec3.hpp"

class Ray {
private:
    Point3 orig;
    Vec3 dir;
    double tm;

public:
    Ray() = default;

    Ray(const Point3& origin, const Vec3& direction, double time);

    Point3 get_origin() const;

    Vec3 get_direction() const;

    double get_time() const;

    Point3 at(double t) const;
};

#endif
