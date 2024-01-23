
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "vector.h"
#include "ppm.h"
#include "ray.h"


typedef struct Sphere Sphere;
struct Sphere { V3 center; double radius; };

double hit_sphere(Ray r, Sphere s) {
    V3 co = v3_sub(r.origin, s.center);
    double a = v3_sqnorm(r.direction);
    double half_b = v3_dot(r.direction, co);
    double c = v3_sqnorm(co) - s.radius*s.radius;
    double discriminant = half_b*half_b - a*c;
    if (discriminant < 0)
        return -1;
    else
        return (-half_b - sqrt(discriminant)) / a;
}

RGB ray_color(Ray r) {
    static const Sphere s = {.center={0, 0, -1}, .radius=0.5};
    double t = hit_sphere(r, s);
    if (t > 0.0) {
        V3 n = v3_unit(v3_sub(ray_at(r, t), s.center));
        return (RGB) {0.5*(n.x + 1), 0.5*(n.y + 1), 0.5*(n.z + 1)};
    }
    else {
        double t = 0.5 * v3_unit(r.direction).y + 0.5;
        RGB light_blue = {0.5, 0.7, 1.0};
        return rgb_blend(WHITE, light_blue, t);
    }
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

