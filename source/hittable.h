#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>
#include "vector.h"
#include "ray.h"

typedef struct Hit Hit;
struct Hit {
    V3 point;
    V3 normal;
    double time;
    bool front_face;
};

typedef struct Hittable Hittable;
struct Hittable {
    bool (*hit)(Hittable *self, Ray r, double tmin, double tmax, Hit *record);
};

#endif // HITTABLE_H