#ifndef METAL_H
#define METAL_H

#include "material.h"

typedef struct Metal Metal;

struct Metal {
    struct Material;
    RGB albedo;
    double fuzz;
};

bool metal_scatter(
    const Material *material, const Hit *hit, RGB *attenuation, Ray *scattered
);


#endif // METAL_H