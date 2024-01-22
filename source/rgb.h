#ifndef RGB_H
#define RGB_H

typedef struct RGB RGB;
struct RGB { double r, g, b; };

extern const RGB BLACK;
extern const RGB WHITE;

RGB rgb_blend(RGB a, RGB b, double t);

#endif // RGB_H