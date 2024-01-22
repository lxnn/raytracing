
#include <assert.h>
#include <stdlib.h>

#include "vector.h"
#include "ppm.h"

typedef struct Ray Ray;
struct Ray { V3 origin; V3 direction; };

V3 ray_at(Ray r, double t) {
    return v3_add(r.origin, v3_scale(r.direction, t));
}

RGB ray_color(Ray r) {
    double t = 0.5 * v3_unit(r.direction).y + 0.5;
    RGB light_blue = {0.5, 0.7, 1.0};
    return rgb_blend(WHITE, light_blue, t);
}

int main() {
    double aspect_ratio = 16.0 / 9.0;
    size_t image_height = 400;
    size_t image_width = (size_t) (image_height * aspect_ratio);
    assert(image_width > 0);

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height / image_height * image_width;
    V3 camera_center = (V3) {0, 0, 0};

    V3 viewport_u = (V3) {viewport_width, 0, 0};
    V3 viewport_v = (V3) {0, -viewport_height, 0};

    V3 pixel_du = v3_scale(viewport_u, 1 / (double) image_width);
    V3 pixel_dv = v3_scale(viewport_v, 1 / (double) image_height);

    V3 viewport_center = v3_add(camera_center, (V3) {0, 0, -focal_length});
    V3 viewport_upper_left = v3_sub(
        viewport_center,
        v3_scale(v3_add(viewport_u, viewport_v), 0.5)
    );
    V3 pixel_zero = v3_add(
        viewport_upper_left,
        v3_scale(v3_add(pixel_du, pixel_dv), 0.5)
    );

    RGB *image = calloc(image_width * image_height, sizeof(RGB));

    for (size_t i = 0; i < image_height; i++) {
        fprintf(stderr, "\rProgress: %d%%", (int) (100.0 * i / image_height));
        fflush(stderr);
        for (size_t j = 0; j < image_width; j++) {
            V3 pixel_offset = v3_add(
                v3_scale(pixel_du, (double) j),
                v3_scale(pixel_dv, (double) i)
            );
            V3 pixel_center = v3_add(pixel_zero, pixel_offset);
            Ray r = (Ray) {
                .origin = camera_center,
                .direction = v3_sub(pixel_center, camera_center),
            };
            image[i * image_width + j] = ray_color(r);
        }
    }

    write_ppm(stdout, image, image_height, image_width);

    fprintf(stderr, "\rDone.                      \n");
}

