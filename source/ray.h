#ifndef RAY_H
#define RAY_H

#include "vector.h"

typedef struct Ray Ray;
struct Ray {V3 origin; V3 direction;};

V3 ray_at(Ray r, double t);

#endif // RAY_H