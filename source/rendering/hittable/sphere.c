#include <rendering/hittable/sphere.h>

#include <stdbool.h>
#include <math.h>

bool sphere_hit(Hittable *self, Ray r, Interval in, Hit *record) {
    Sphere *s = (Sphere *) self;
    V3 co = v3_sub(r.origin, s->center);
    double a = v3_sqnorm(r.direction);
    double half_b = v3_dot(r.direction, co);
    double c = v3_sqnorm(co) - s->radius*s->radius;

    double discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;

    double sqrtd = sqrt(discriminant);

    double root = (-half_b - sqrtd) / a;
    if (!interval_surrounds(in, root)) root = (-half_b + sqrtd) / a;
    if (!interval_surrounds(in, root)) return false;

    record->time = root;
    record->point = ray_at(r, root);
    V3 front_normal = v3_scale(
        v3_sub(record->point, s->center),
        1 / s->radius
    );
    record->front_face = v3_dot(r.direction, front_normal) < 0;
    record->normal = record->front_face? front_normal : v3_neg(front_normal);

    record->ray_in = r;

    record->material = self->material;

    return true;
}
