#include "vec3.hpp"

using std::sqrt;

Vec3::Vec3()
        :x(0), y(0), z(0) { }

Vec3::Vec3(double _x, double _y, double _z)
        :x(_x), y(_y), z(_z) { }

Vec3 Vec3::operator-() const
{
    return {-x, -y, -z};
}

Vec3& Vec3::operator+=(const Vec3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec3& Vec3::operator*=(const double t)
{
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

Vec3& Vec3::operator/=(const double t)
{
    return *this *= 1/t;
}

double Vec3::operator[](int i) const
{
    if (i==0)
        return x;
    else if (i==1)
        return y;
    else if (i==2)
        return z;
    else
        throw std::invalid_argument("i must be a 0, 1 or 2");
}

double& Vec3::operator[](int i)
{
    if (i==0)
        return x;
    else if (i==1)
        return y;
    else if (i==2)
        return z;
    else
        throw std::invalid_argument("i must be a 0, 1 or 2");
}

double Vec3::length() const
{
    return sqrt(length_squared());
}

double Vec3::length_squared() const
{
    return x*x+y*y+z*z;
}

bool Vec3::near_zero() const
{
    // Return true if the vector is close to zero in all dimensions.
    const double s = 1e-8;
    return (fabs(x)<s) && (fabs(y)<s) && (fabs(z)<s);
}



