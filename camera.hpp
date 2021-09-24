#ifndef RAY_TRACER_CAMERA_HPP
#define RAY_TRACER_CAMERA_HPP

#include "utilities.hpp"
#include "vec3.hpp"
#include "ray.hpp"

class Camera {
private:
    Point3 origin;
    Point3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    double lens_radius;
    double time0, time1;

public:
    Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, double vfov,
            double aspect_ratio, double aperture, double focus_dist, double _time0 = 0,
            double _time1 = 0); // vfov means vertical field-of-view in degrees

    Ray get_ray(double s, double t) const;
};

#endif
