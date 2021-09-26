#ifndef RAY_TRACER_PERLIN_HPP
#define RAY_TRACER_PERLIN_HPP

#include "vec3.hpp"

class Perlin {
private:
    static const int point_count = 256;
    Vec3* ranvec;
    int* perm_x;
    int* perm_y;
    int* perm_z;

    static int* perlin_generate_perm();

    static void permute(int* p, int n);

public:
    Perlin();

    ~Perlin();

    double noise(const Point3& p) const;

    static double perlin_interp(Vec3 c[2][2][2], double u, double v, double w);

    double turb(const Point3& p, int depth = 7) const;
};

#endif
