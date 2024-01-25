#ifndef RANDOM_H
#define RANDOM_H

#include "vector.h"

double random();
double randrange(double min, double max);
double random_normal();
V3 randrange_3d(double min, double max);
V3 random_normal_3d();
V3 random_on_unit_sphere();
V3 random_on_hemisphere(V3 normal);
V3 random_on_unit_disk();


#endif // RANDOM_H