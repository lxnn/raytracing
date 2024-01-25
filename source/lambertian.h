#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

typedef struct Lambertian Lambertian;

struct Lambertian {
    struct Material;
    RGB albedo;
};

bool lambertian_scatter(
    const Material *material, const Hit *hit, RGB *attenuation, Ray *scattered
);


#endif // LAMBERTIAN_H