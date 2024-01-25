#include <rendering/camera.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <rendering/material/material.h>
#include <util/random.h>

#define TAU 6.283185307179586476
#define RAD_PER_DEG (TAU/360.0)

void camera_dump_config(FILE *file, Camera *camera) {
    fprintf(
        file,
        "image_height=%llu image_width=%llu\n"
        "center=(%f, %f, %f)\n"
        "lookat=(%f, %f, %f)\n"
        "up=(%f, %f, %f)\n"
        "vfov=%f\n"
        "samples_per_pixel=%llu\n"
        "max_bounces=%llu\n"
        "is_init=%d\n"
        "aspect_ratio=%f\n"
        "u=(%f, %f, %f) v=(%f, %f, %f) w=(%f, %f, %f)\n"
        "focal_length=%f\n"
        "viewport_height=%f viewport_width=%f\n"
        "viewport_upper_left=(%f, %f, %f)\n"
        "pixel_row_delta=(%f, %f, %f) pixel_col_delta=(%f, %f, %f)\n",
        camera->image_height, camera->image_width,
        camera->center.x, camera->center.y, camera->center.z,
        camera->lookat.x, camera->lookat.y, camera->lookat.z,
        camera->up.x, camera->up.y, camera->up.z,
        camera->vfov,
        camera->samples_per_pixel,
        camera->max_bounces,
        camera->priv.is_init,
        camera->priv.aspect_ratio,
        camera->priv.u.x, camera->priv.u.y, camera->priv.u.z,
        camera->priv.v.x, camera->priv.v.y, camera->priv.v.z,
        camera->priv.w.x, camera->priv.w.y, camera->priv.w.z,
        camera->priv.focal_length,
        camera->priv.viewport_height, camera->priv.viewport_width,
        camera->priv.viewport_upper_left.x, camera->priv.viewport_upper_left.y, camera->priv.viewport_upper_left.z,
        camera->priv.pixel_row_delta.x, camera->priv.pixel_row_delta.y, camera->priv.pixel_row_delta.z,
        camera->priv.pixel_col_delta.x, camera->priv.pixel_col_delta.y, camera->priv.pixel_col_delta.z
    );
}

static void init(Camera *camera) {
    camera->priv.aspect_ratio = (double) camera->image_width / camera->image_height;
    camera->priv.focal_length = v3_norm(v3_sub(camera->lookat, camera->center));
    camera->priv.viewport_height = 2 * camera->priv.focal_length * tan(RAD_PER_DEG * camera->vfov / 2);
    camera->priv.viewport_width = camera->priv.viewport_height * camera->priv.aspect_ratio;

    camera->priv.w = v3_unit(v3_sub(camera->center, camera->lookat));
    camera->priv.u = v3_unit(v3_cross(camera->up, camera->priv.w));
    camera->priv.v = v3_cross(camera->priv.w, camera->priv.u);

    camera->priv.pixel_row_delta = v3_scale(
        camera->priv.v,
        -1 * camera->priv.viewport_height / camera->image_height
    );
    camera->priv.pixel_col_delta = v3_scale(
        camera->priv.u,
        camera->priv.viewport_width / camera->image_width
    );

    camera->priv.viewport_upper_left = v3_add3(
        camera->lookat,
        v3_scale(camera->priv.u, -1 * camera->priv.viewport_width / 2),
        v3_scale(camera->priv.v, camera->priv.viewport_height / 2)
    );

    camera->priv.is_init = true;

    camera_dump_config(stderr, camera);
}


static RGB ray_color(Ray ray, Hittable *world, size_t max_bounces) {
    Hit record;
    if (max_bounces == 0) {
        return (RGB) {0, 0, 0};
    }
    else if (world->hit(world, ray, (Interval) {0.001, INFINITY}, &record)) {
        RGB attenuation;
        Ray scattered_ray;
        if (record.material->scatter(record.material, &record, &attenuation, &scattered_ray))
            return rgb_mul(
                ray_color(scattered_ray, world, max_bounces - 1),
                attenuation
            );
        else
            return (RGB) {0, 0, 0};
    }
    else {
        double a = 0.5 * v3_unit(ray.direction).y + 0.5;
        RGB light_blue = {0.5, 0.7, 1.0};
        return rgb_blend(WHITE, light_blue, a);
    }
}

static Ray get_ray(Camera *camera, size_t i, size_t j) {
    V3 pixel_corner = v3_add3(
        camera->priv.viewport_upper_left,
        v3_scale(camera->priv.pixel_col_delta, j + 0.5),
        v3_scale(camera->priv.pixel_row_delta, i + 0.5)
    );
    V3 random_offset = v3_add(
        v3_scale(camera->priv.pixel_col_delta, random()),
        v3_scale(camera->priv.pixel_row_delta, random())
    );
    V3 sample_point = v3_add(pixel_corner, random_offset);
    return (Ray) {
        .origin = camera->center,
        .direction = v3_sub(sample_point, camera->center),
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
