#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

typedef struct V3 V3;
struct V3 {double x, y, z;};

V3 v3_add(V3 a, V3 b);
V3 v3_add3(V3 a, V3 b, V3 c);
V3 v3_add4(V3 a, V3 b, V3 c, V3 d);
V3 v3_sub(V3 a, V3 b);
V3 v3_mul(V3 a, V3 b);
V3 v3_scale(V3 a, double s);
V3 v3_neg(V3 a);
double v3_sum(V3 a);
double v3_dot(V3 a, V3 b);
double v3_sqnorm(V3 a);
double v3_norm(V3 a);
V3 v3_cross(V3 a, V3 b);
V3 v3_unit(V3 a);
void v3_iadd(V3 *a, V3 b);
void v3_isub(V3 *a, V3 b);
void v3_imul(V3 *a, V3 b);
void v3_iscale(V3 *a, double s);
void v3_ineg(V3 *a);
bool v3_near_zero(V3 a);

#endif // VECTOR_H