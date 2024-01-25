#include <imaging/rgb.h>

#include <math.h>

const RGB BLACK = { 0.0, 0.0, 0.0 };
const RGB WHITE = { 1.0, 1.0, 1.0 };

RGB rgb_blend(RGB a, RGB b, double t) {
    return (RGB) {
        (1-t) * a.r + t * b.r,
        (1-t) * a.g + t * b.g,
        (1-t) * a.b + t * b.b,
    };
}

RGB rgb_average(RGB *samples, size_t n) {
    RGB sum = (RGB) {0, 0, 0};
    for (size_t i = 0; i < n; i++) {
        sum.r += samples[i].r;
        sum.g += samples[i].g;
        sum.b += samples[i].b;
    }
    return (RGB) {sum.r / n, sum.g / n, sum.b / n};
}

RGB rgb_scale(RGB rgb, double s) {
    return (RGB) {rgb.r*s, rgb.g*s, rgb.b*s};
}

RGB rgb_mul(RGB a, RGB b) {
    return (RGB) {a.r*b.r, a.g*b.g, a.b*b.b};
}

bool rgb_valid(RGB rgb) {
    return (
            rgb.r >= 0 && rgb.r <= 1
        &&  rgb.g >= 0 && rgb.g <= 1
        &&  rgb.b >= 0 && rgb.b <= 1
    );
}

RGB rgb_linear_to_gamma(RGB rgb) {
    return (RGB) {sqrt(rgb.r), sqrt(rgb.g), sqrt(rgb.b)};
}

RGB rgb_from_v3(V3 v) {
    return (RGB) {v.x, v.y, v.z};
};