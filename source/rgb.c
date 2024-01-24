#include "rgb.h"

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