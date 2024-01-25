#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdbool.h>
#include "rgb.h"
#include "ray.h"

typedef struct Hit Hit;

typedef struct Material Material;
struct Material {
    bool (*scatter)(const Material *material, const Hit *hit, RGB *attenuation, Ray *scattered);
};

#endif // MATERIAL_H