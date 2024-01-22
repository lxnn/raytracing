#ifndef VECTOR_H
#define VECTOR_H

typedef struct V3 V3;
struct V3 {double x, y, z;};

V3 v3_add(V3 a, V3 b);
V3 v3_sub(V3 a, V3 b);
V3 v3_mul(V3 a, V3 b);
V3 v3_scale(V3 a, double s);
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

#endif // VECTOR_H