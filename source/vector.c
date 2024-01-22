#include "vector.h"
#include <math.h>

V3 v3_add(V3 a, V3 b) { return (V3){a.x+b.x, a.y+b.y, a.z+b.z}; }
V3 v3_sub(V3 a, V3 b) { return (V3){a.x-b.x, a.y-b.y, a.z-b.z}; }
V3 v3_mul(V3 a, V3 b) { return (V3){a.x*b.x, a.y*b.y, a.z*b.z}; }
V3 v3_scale(V3 a, double s) { return (V3){a.x*s, a.y*s, a.z*s}; }
double v3_sum(V3 a) { return a.x + a.y + a.z; }
double v3_dot(V3 a, V3 b) { return v3_sum(v3_mul(a, b)); }
double v3_sqnorm(V3 a) { return v3_dot(a, a); }
double v3_norm(V3 a) { return sqrt(v3_dot(a, a)); }
V3 v3_cross(V3 a, V3 b) {
    return (V3){a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x };
}
V3 v3_unit(V3 a) { return v3_scale(a, 1/v3_norm(a)); }
void v3_iadd(V3 *a, V3 b) { a->x += b.x; a->y += b.y; a->z += b.z; }
void v3_isub(V3 *a, V3 b) { a->x -= b.x; a->y -= b.y; a->z -= b.z;}
void v3_imul(V3 *a, V3 b) { a->x *= b.x; a->y *= b.y; a->z *= b.z;}
void v3_iscale(V3 *a, double s) { a->x *= s; a->y *= s; a->z *= s; }
