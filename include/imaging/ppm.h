#ifndef PPM_H
#define PPM_H

#include <stdio.h>

#include <imaging/image.h>

void write_ppm(FILE *file, Image *image);

#endif // PPM_H