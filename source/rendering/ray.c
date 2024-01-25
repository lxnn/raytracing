#include <rendering/ray.h>

V3 ray_at(Ray r, double t) {
    return v3_add(r.origin, v3_scale(r.direction, t));
}
