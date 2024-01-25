#include "metal.h"

#include "hittable.h"

bool metal_scatter(
    const Material *material, const Hit *record, RGB *attenuation, Ray *scattered
) {
    Metal *metal = (Metal *) material;

    V3 scatter_direction = v3_reflect(record->ray_in.direction, record->normal);
    *scattered = (Ray) {.origin=record->point, .direction=scatter_direction};
    *attenuation = metal->albedo;

    return true;
}