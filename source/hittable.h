#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>
#include "vector.h"
#include "ray.h"
#include "interval.h"

typedef struct Material Material;

typedef struct Hit Hit;
struct Hit {
    V3 point;
    V3 normal;
    double time;
    bool front_face;
    Material *material;
};

typedef struct Hittable Hittable;
struct Hittable {
    bool (*hit)(Hittable *self, Ray r, Interval in, Hit *record);
    Material *material;
};

#endif // HITTABLE_H