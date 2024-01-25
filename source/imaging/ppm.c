#include <imaging/ppm.h>

#include <math.h>
#include <assert.h>

static int convert(double intensity) {
    assert(!isnan(intensity));
    int int_intensity = (int) (intensity * 255);
    if (int_intensity > 255) return 255;
    if (int_intensity < 0) return 0;
    return int_intensity;
}

void write_ppm(FILE *file, Image *image) {
    fprintf(file, "P3\n%zu %zu\n255\n", image->width, image->height);
    for (size_t i = 0; i < image->height; i++) {
        for (size_t j = 0; j < image->width; j++) {
            RGB color = rgb_linear_to_gamma(image->pixels[i * image->width + j]);
            fprintf(file, "%d %d %d ", convert(color.r), convert(color.g), convert(color.b));
        }
        fprintf(file, "\n");
    }
}