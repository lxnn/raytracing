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
};

Image *camera_render(Camera *camera, Hittable *world);

#endif // CAMERA_H