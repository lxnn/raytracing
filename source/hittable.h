#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>
#include "vector.h"
#include "ray.h"
#include "interval.h"

typedef struct Hit Hit;
struct Hit {
    V3 point;
    V3 normal;
    double time;
    bool front_face;
};

typedef struct Hittable Hittable;
struct Hittable {
    bool (*hit)(Hittable *self, Ray r, Interval in, Hit *record);
};

#endif // HITTABLE_H