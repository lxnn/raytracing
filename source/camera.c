#include "camera.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static RGB ray_color(Ray ray, Hittable *world) {
    Hit record;
    if (world->hit(world, ray, (Interval) {0, INFINITY}, &record)) {
        return (RGB) {
            0.5*(record.normal.x + 1),
            0.5*(record.normal.y + 1),
            0.5*(record.normal.z + 1),
        };
    }
    else {
        double a = 0.5 * v3_unit(ray.direction).y + 0.5;
        RGB light_blue = {0.5, 0.7, 1.0};
        return rgb_blend(WHITE, light_blue, a);
    }
}

Image *camera_render(Camera *camera, Hittable *world) {
    double aspect_ratio = (double) camera->image_width / camera->image_height;
    double viewport_width = camera->viewport_height * aspect_ratio;

    V3 viewport_u = (V3) {viewport_width, 0, 0};
    V3 viewport_v = (V3) {0, -camera->viewport_height, 0};

    V3 pixel_du = v3_scale(viewport_u, 1.0 / camera->image_width);
    V3 pixel_dv = v3_scale(viewport_v, 1.0 / camera->image_height);

    V3 viewport_center = v3_add(camera->center, (V3) {0, 0, -camera->focal_length});
    V3 viewport_upper_left = v3_sub(
        viewport_center,
        v3_scale(v3_add(viewport_u, viewport_v), 0.5)
    );
    V3 pixel_zero = v3_add(
        viewport_upper_left,
        v3_scale(v3_add(pixel_du, pixel_dv), 0.5)
    );

    Image *image = malloc(sizeof(Image));
    image->height = camera->image_height;
    image->width = camera->image_width;
    image->pixels = calloc(image->height * image->width, sizeof(RGB));

    for (size_t i = 0; i < image->height; i++) {
        fprintf(stderr, "\rProgress: %d%%", (int) (100.0 * i / image->height));
        fflush(stderr);
        for (size_t j = 0; j < image->width; j++) {
            V3 pixel_offset = v3_add(
                v3_scale(pixel_du, (double) j),
                v3_scale(pixel_dv, (double) i)
            );
            V3 pixel_center = v3_add(pixel_zero, pixel_offset);
            Ray ray = (Ray) {
                .origin = camera->center,
                .direction = v3_sub(pixel_center, camera->center),
            };
            image->pixels[i * image->width + j] = ray_color(ray, world);
        }
    }

    fprintf(stderr, "\rProgress: 100%%\n");

    return image;
}
