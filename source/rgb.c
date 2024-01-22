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
