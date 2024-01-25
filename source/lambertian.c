#include "lambertian.h"

#include "hittable.h"
#include "random.h"

bool lambertian_scatter(
    const Material *material, const Hit *record, RGB *attenuation, Ray *scattered
) {
    Lambertian *lambertian = (Lambertian *) material;

    V3 scatter_direction = v3_add(record->normal, random_on_unit_sphere());
    if (v3_near_zero(scatter_direction))
        scatter_direction = record->normal;

    *scattered = (Ray) {.origin=record->point, .direction=scatter_direction};
    *attenuation = lambertian->albedo;

    return true;
}