#include "ppm.h"
#include <stdio.h>

void write_ppm(FILE *file, RGB *data, size_t height, size_t width) {
    fprintf(file, "P3\n%zu %zu\n255\n", width, height);
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            RGB pixel = data[i * width + j];
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
