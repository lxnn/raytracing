#include <rendering/material/metal.h>

#include <util/random.h>

bool metal_scatter(
    const Material *material, const Hit *record, RGB *attenuation, Ray *scattered
) {
    Metal *metal = (Metal *) material;

    V3 reflected = v3_reflect(v3_unit(record->ray_in.direction), record->normal);
    V3 scatter_direction = v3_add(reflected, v3_scale(random_on_unit_sphere(), metal->fuzz));
    *scattered = (Ray) {.origin=record->point, .direction=scatter_direction};
    *attenuation = metal->albedo;

    return v3_dot(scatter_direction, record->normal) > 0.0;
}