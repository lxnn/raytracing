#ifndef LIST_H
#define LIST_H

#include "hittable.h"

typedef struct List List;

struct List {
    struct Hittable;
    Hittable **objects;
    size_t count;
};

bool list_hit(Hittable *self, Ray r, Interval in, Hit *record);

#endif // LIST_H