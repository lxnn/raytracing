#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vector.h"

typedef struct Sphere Sphere;
struct Sphere {
    struct Hittable;
    V3 center;
    double radius;
};

bool sphere_hit(Hittable *self, Ray r, double tmin, double tmax, Hit *record);

#endif // SPHERE_H