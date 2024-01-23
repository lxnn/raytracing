#include "ppm.h"

#include <stdio.h>

void write_ppm(FILE *file, Image *image) {
    fprintf(file, "P3\n%zu %zu\n255\n", image->width, image->height);
    for (size_t i = 0; i < image->height; i++) {
        for (size_t j = 0; j < image->width; j++) {
            RGB pixel = image->pixels[i * image->width + j];
            fprintf(
                file,
                "%d %d %d ",
                (int) (255 * pixel.r),
                (int) (255 * pixel.g),
                (int) (255 * pixel.b)
            );
        }
        fprintf(file, "\n");
    }
}
