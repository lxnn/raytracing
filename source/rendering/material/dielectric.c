#include "util/vector.h"
#include <rendering/material/dielectric.h>

#include <assert.h>
#include <math.h>

#include <util/random.h>

static V3 refract(V3 in, V3 normal, double ir_ratio) {
    assert(v3_isunit(in));
    assert(v3_isunit(normal));
    double cos_theta = -v3_dot(in, normal);
    V3 out_perp = v3_scale(
        v3_add(in, v3_scale(normal, cos_theta)),
        ir_ratio
    );
    V3 out_parallel = v3_scale(
        normal,
        -sqrt(fabs(1 - v3_sqnorm(out_perp)))
    );
    V3 out = v3_add(out_parallel, out_perp);
    return out;
}

bool dielectric_scatter(
    const Material *material, const Hit *record, RGB *attenuation, Ray *scattered
) {
    Dielectric *dielectric = (Dielectric *) material;

    *attenuation = (RGB) { 1, 1, 1 };

    V3 unit_direction = v3_unit(record->ray_in.direction);
    double ir_ratio = record->front_face ? (1/dielectric->ir) : dielectric->ir;
    V3 refracted = refract(unit_direction, record->normal, ir_ratio);

    scattered->origin = record->point;
    scattered->direction = refracted;

    return true;
}