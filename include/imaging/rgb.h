#ifndef RGB_H
#define RGB_H

#include <stdbool.h>

#include <util/vector.h>

typedef struct RGB RGB;
struct RGB { double r, g, b; };

extern const RGB BLACK;
extern const RGB WHITE;

RGB rgb_blend(RGB a, RGB b, double t);
RGB rgb_average(RGB *samples, size_t n);
RGB rgb_scale(RGB rgb, double s);
RGB rgb_mul(RGB a, RGB b);
bool rgb_valid(RGB rgb);
RGB rgb_linear_to_gamma(RGB rgb);
RGB rgb_from_v3(V3 v);

#endif // RGB_H