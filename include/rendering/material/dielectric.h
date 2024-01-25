#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"

typedef struct Dielectric Dielectric;

struct Dielectric {
    struct Material;
    double ir;
};

bool dielectric_scatter(
    const Material *material, const Hit *hit, RGB *attenuation, Ray *scattered
);


#endif // DIELECTRIC_H