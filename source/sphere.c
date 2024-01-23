#include "sphere.h"

#include <stdbool.h>
#include <math.h>
#include "ray.h"

bool sphere_hit(Hittable *self, Ray r, double tmin, double tmax, Hit *record) {
    Sphere *s = (Sphere *) self;
    V3 co = v3_sub(r.origin, s->center);
    double a = v3_sqnorm(r.direction);
    double half_b = v3_dot(r.direction, co);
    double c = v3_sqnorm(co) - s->radius*s->radius;

    double discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;

    double sqrtd = sqrt(discriminant);

    double root = (-half_b - sqrtd) / a;
    if (root < tmin || root > tmax) root = (-half_b + sqrtd) / a;
    if (root < tmin || root > tmax) return false;

    record->time = root;
    record->point = ray_at(r, root);
    record->normal = v3_scale(
        v3_sub(record->point, s->center),
        1 / s->radius
    );

    return true;
}
