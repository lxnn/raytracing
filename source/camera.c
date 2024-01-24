#include "camera.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define TAU 6.283185307179586476

static void init(Camera *camera) {
    camera->priv.aspect_ratio = (double) camera->image_width / camera->image_height;
    camera->priv.viewport_width = camera->viewport_height * camera->priv.aspect_ratio;

    camera->priv.viewport_u = (V3) {camera->priv.viewport_width, 0, 0};
    camera->priv.viewport_v = (V3) {0, -camera->viewport_height, 0};

    camera->priv.pixel_du = v3_scale(camera->priv.viewport_u, 1.0 / camera->image_width);
    camera->priv.pixel_dv = v3_scale(camera->priv.viewport_v, 1.0 / camera->image_height);

    camera->priv.viewport_center = v3_add(camera->center, (V3) {0, 0, -camera->focal_length});
    camera->priv.viewport_upper_left = v3_sub(
        camera->priv.viewport_center,
        v3_scale(v3_add(camera->priv.viewport_u, camera->priv.viewport_v), 0.5)
    );
    camera->priv.pixel_zero = v3_add(
        camera->priv.viewport_upper_left,
        v3_scale(v3_add(camera->priv.pixel_du, camera->priv.pixel_dv), 0.5)
    );

    camera->priv.is_init = true;
}

static double random() {
    return rand() / (RAND_MAX + 1.0);
}

static double random_normal() {
    return sqrt(-2.0 * log(1 - random())) * cos(TAU * random());
}

static V3 random_normal_3d() {
    return (V3) {random_normal(), random_normal(), random_normal()};
}

static V3 random_on_unit_sphere() {
    return v3_unit(random_normal_3d());
}

static V3 random_on_hemisphere(V3 normal) {
    V3 on_unit_sphere = random_on_unit_sphere();
    return v3_dot(on_unit_sphere, normal) > 0 ? on_unit_sphere : v3_neg(on_unit_sphere);
}

static RGB ray_color(Ray ray, Hittable *world, size_t max_bounces) {
    Hit record;
    if (max_bounces == 0) {
        return (RGB) {0, 0, 0};
    }
    else if (world->hit(world, ray, (Interval) {0, INFINITY}, &record)) {
        V3 new_direction = random_on_hemisphere(record.normal);
        assert(v3_sqnorm(new_direction) > 0.0);
        Ray reflected_ray = (Ray) {.origin=record.point, .direction=new_direction};
        RGB color = ray_color(reflected_ray, world, max_bounces - 1);
        return rgb_scale(color, 0.5);
    }
    else {
        double a = 0.5 * v3_unit(ray.direction).y + 0.5;
        RGB light_blue = {0.5, 0.7, 1.0};
        return rgb_blend(WHITE, light_blue, a);
    }
}

static Ray get_ray(Camera *camera, size_t i, size_t j) {
    V3 pixel_corner_offset = v3_add(
        v3_scale(camera->priv.pixel_du, (double) j),
        v3_scale(camera->priv.pixel_dv, (double) i)
    );
    V3 random_offset = v3_add(
        v3_scale(camera->priv.pixel_du, random()),
        v3_scale(camera->priv.pixel_dv, random())
    );
    V3 pixel_sample = v3_add3(
        camera->priv.pixel_zero,
        pixel_corner_offset,
        random_offset
    );
    return (Ray) {
        .origin = camera->center,
        .direction = v3_sub(pixel_sample, camera->center),
    };
}

Image *camera_render(Camera *camera, Hittable *world) {
    if (camera->priv.is_init != true) init(camera);

    Image *image = malloc(sizeof(Image));
    image->height = camera->image_height;
    image->width = camera->image_width;
    image->pixels = calloc(image->height * image->width, sizeof(RGB));

    RGB *samples = calloc(camera->samples_per_pixel, sizeof(RGB));

    for (size_t i = 0; i < image->height; i++) {
        fprintf(stderr, "\rProgress: %d%%", (int) (100.0 * i / image->height));
        fflush(stderr);
        for (size_t j = 0; j < image->width; j++) {
            for (size_t k = 0; k < camera->samples_per_pixel; k++) {
                Ray ray = get_ray(camera, i, j);
                RGB sample = ray_color(ray, world, camera->max_bounces);
                if (!rgb_valid(sample)) {
                    fprintf(
                        stderr, "\nInvalid sample: r=%f g=%f b=%f\n", sample.r, sample.g, sample.b
                    );
                    assert(false);
                }
                samples[k] = sample;
            }
            image->pixels[i * image->width + j] = rgb_average(samples, camera->samples_per_pixel);
        }
    }

    fprintf(stderr, "\rProgress: 100%%\n");

    return image;
}
