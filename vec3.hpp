#ifndef RAY_TRACER_VEC3_HPP
#define RAY_TRACER_VEC3_HPP

#include "utilities.hpp"

#include <cmath>
#include <iostream>

class Vec3 {
public:
    double x, y, z;

    Vec3();

    Vec3(double _x, double _y, double _z);

    Vec3 operator-() const;

    Vec3& operator+=(const Vec3& v);

    Vec3& operator*=(double t);

    Vec3& operator/=(double t);

    double operator[](int i) const;

    double& operator[](int i);

    double length() const;

    double length_squared() const;

    bool near_zero() const;

    inline static Vec3 random()
    {
        return {random_double(), random_double(), random_double()};
    }

    inline static Vec3 random(double min, double max)
    {
        return {random_double(min, max), random_double(min, max), random_double(min, max)};
    }
};

// Type aliases for Vec3
using Point3 = Vec3;  // 3D point
using Color = Vec3;   // RGB color

// Vec3 Utility Functions

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
    return {u.x+v.x, u.y+v.y, u.z+v.z};
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
    return {u.x-v.x, u.y-v.y, u.z-v.z};
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
    return {u.x*v.x, u.y*v.y, u.z*v.z};
}

inline Vec3 operator*(double t, const Vec3& v)
{
    return {t*v.x, t*v.y, t*v.z};
}

inline Vec3 operator*(const Vec3& v, double t)
{
    return t*v;
}

inline Vec3 operator/(Vec3 v, double t)
{
    return (1/t)*v;
}

inline double dot(const Vec3& u, const Vec3& v)
{
    return u.x*v.x+u.y*v.y+u.z*v.z;
}

inline Vec3 cross(const Vec3& u, const Vec3& v)
{
    return {u.y*v.z-u.z*v.y,
            u.z*v.x-u.x*v.z,
            u.x*v.y-u.y*v.x};
}

inline Vec3 unit_vector(Vec3 v)
{
    return v/v.length();
}

inline Vec3 random_in_unit_sphere()
{
    while (true) {
        Vec3 p = Vec3::random(-1, 1);
        if (p.length_squared()>=1)
            continue;
        return p;
    }
}

inline Vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}

inline Vec3 random_in_hemisphere(const Vec3& normal)
{
    Vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal)>0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

inline Vec3 random_in_unit_disk()
{
    while (true) {
        Vec3 p = Vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared()>=1)
            continue;
        return p;
    }
}

inline Vec3 reflect(const Vec3& v, const Vec3& n)
{
    return v-2*dot(v, n)*n;
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat)
{
    double cos_theta = fmin(dot(-uv, n), 1.0);
    Vec3 r_out_perp = etai_over_etat*(uv+cos_theta*n);
    Vec3 r_out_parallel = -sqrt(fabs(1.0-r_out_perp.length_squared()))*n;
    return r_out_perp+r_out_parallel;
}

#endif
