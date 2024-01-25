#include <util/random.h>

#include <stdlib.h>
#include <math.h>

#define TAU 6.283185307179586476

double random() {
    return rand() / (RAND_MAX + 1.0);
}

double random_normal() {
    return sqrt(-2.0 * log(1 - random())) * cos(TAU * random());
}

V3 random_normal_3d() {
    return (V3) {random_normal(), random_normal(), random_normal()};
}

V3 random_on_unit_sphere() {
    return v3_unit(random_normal_3d());
}

V3 random_on_hemisphere(V3 normal) {
    V3 on_unit_sphere = random_on_unit_sphere();
    return v3_dot(on_unit_sphere, normal) > 0 ? on_unit_sphere : v3_neg(on_unit_sphere);
}