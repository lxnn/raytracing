
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "vector.h"
#include "ppm.h"
#include "ray.h"
#include "hittable.h"
#include "sphere.h"
#include "list.h"
#include "camera.h"


int main() {
    Sphere spheres[] = {
        {.hit=sphere_hit, .center={0, 0, -1}, .radius=0.5},
        {.hit=sphere_hit, .center={0, -100.5, -1}, .radius=100},
    };
    Hittable *objects[] = {
        (Hittable *) &spheres[0],
        (Hittable *) &spheres[1],
    };
    List object_list = {.hit=list_hit, .objects=objects, .count=2};
    Hittable *world = (Hittable *) &object_list;

    Camera camera = {
        .image_height = 450,
        .image_width = 800,
        .center = (V3) {0, 0, 0},
        .focal_length = 1.0,
        .viewport_height = 2.0,
        .samples_per_pixel = 100,
        .max_bounces = 50,
    };

    Image *image = camera_render(&camera, world);

    write_ppm(stdout, image);
}

