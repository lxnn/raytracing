#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>

#include <rendering/hittable/hittable.h>
#include <imaging/image.h>

typedef struct Camera Camera;
struct Camera {
    size_t image_height, image_width;
    V3 center;
    V3 lookat;
    V3 up;
    double vfov;
    size_t samples_per_pixel;
    size_t max_bounces;

    struct {
        bool is_init;
        double aspect_ratio;
        V3 u, v, w; // Camera coordinate system
        double focal_length;
        double viewport_height, viewport_width;
        V3 viewport_upper_left;
        V3 pixel_row_delta, pixel_col_delta;
    } priv;
};

Image *camera_render(Camera *camera, Hittable *world);
void camera_dump_config(FILE *file, Camera *camera);

#endif // CAMERA_H