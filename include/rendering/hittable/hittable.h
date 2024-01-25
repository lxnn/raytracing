#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>

#include <util/interval.h>
#include <rendering/ray.h>

typedef struct Material Material;

typedef struct Hit Hit;
struct Hit {
    V3 point;
    V3 normal;
    double time;
    bool front_face;
    Material *material;
    Ray ray_in;
};

typedef struct Hittable Hittable;
struct Hittable {
    bool (*hit)(Hittable *self, Ray r, Interval in, Hit *record);
    Material *material;
};

#endif // HITTABLE_H