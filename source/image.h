#ifndef IMAGE_H
#define IMAGE_H

#include "rgb.h"

typedef struct Image Image;
struct Image {
    size_t height;
    size_t width;
    RGB *pixels;
};

#endif // IMAGE_H
