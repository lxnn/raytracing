#ifndef RGB_H
#define RGB_H

typedef struct RGB RGB;
struct RGB { double r, g, b; };

extern const RGB BLACK;
extern const RGB WHITE;

RGB rgb_blend(RGB a, RGB b, double t);
RGB rgb_average(RGB *samples, size_t n);
RGB rgb_scale(RGB rgb, double s);

#endif // RGB_H