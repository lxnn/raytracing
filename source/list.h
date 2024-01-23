#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

typedef struct List List;

struct List {
    struct Hittable;
    Hittable **elements;
    size_t length;
    size_t capacity;
};

bool list_hit(Hittable *self, Ray r, double tmin, double tmax, Hit *record);
void list_init(List *self, size_t capacity);
void list_destroy(List *self);
void list_append(List *self, Hittable *hittable);

#endif // SPHERE_H