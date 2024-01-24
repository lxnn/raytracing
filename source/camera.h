#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "vector.h"
#include "image.h"

typedef struct Camera Camera;
struct Camera {
    size_t image_height;
    size_t image_width;
    V3 center;
    double focal_length;
    double viewport_height;

    struct {
        bool is_init;
        double aspect_ratio;
        double viewport_width;
        V3 viewport_upper_left;
        V3 viewport_u;
        V3 viewport_v;
        V3 pixel_du;
        V3 pixel_dv;
        V3 viewport_center;
        V3 pixel_zero;
    } priv;
};

Image *camera_render(Camera *camera, Hittable *world);

#endif // CAMERA_H