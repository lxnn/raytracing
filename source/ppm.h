#ifndef PPM_H
#define PPM_H

#include "rgb.h"
#include <stdio.h>

void write_ppm(FILE *file, RGB *data, size_t height, size_t width);

#endif // PPM_H