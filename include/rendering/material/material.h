#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdbool.h>

#include <imaging/rgb.h>
#include <rendering/ray.h>
#include <rendering/hittable/hittable.h>

typedef struct Material Material;
struct Material {
    bool (*scatter)(const Material *material, const Hit *hit, RGB *attenuation, Ray *scattered);
};

#endif // MATERIAL_H