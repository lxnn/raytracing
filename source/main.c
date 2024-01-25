
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
#include "lambertian.h"
#include "metal.h"


int main() {
    Lambertian diffuse_grey_ = {
        .scatter=lambertian_scatter,
        .albedo={0.5, 0.5, 0.5},
    };
    Lambertian diffuse_yellow_ = {
        .scatter=lambertian_scatter,
        .albedo={0.8, 0.8, 0.0},
    };
    Metal silver_ = {
        .scatter=metal_scatter,
        .albedo={0.8, 0.8, 0.8},
    };
    Metal gold_ = {
        .scatter=metal_scatter,
        .albedo={0.8, 0.6, 0.2},
    };

    Material *diffuse_grey = (Material *) &diffuse_grey_;
    Material *diffuse_yellow = (Material *) &diffuse_yellow_;
    Material *silver = (Material *) &silver_;
    Material *gold = (Material *) &gold_;

    Sphere spheres[] = {
        {.hit=sphere_hit, .material=diffuse_grey, .center={0, 0, -1}, .radius=0.5},
        {.hit=sphere_hit, .material=diffuse_yellow, .center={0, -100.5, -1}, .radius=100},
        {.hit=sphere_hit, .material=silver, .center={-1, 0, -1}, .radius=0.5},
        {.hit=sphere_hit, .material=gold, .center={1, 0, -1}, .radius=0.5},
    };
    Hittable *objects[] = {
        (Hittable *) &spheres[0],
        (Hittable *) &spheres[1],
        (Hittable *) &spheres[2],
        (Hittable *) &spheres[3],
    };
    List object_list = {.hit=list_hit, .objects=objects, .count=sizeof(objects)/sizeof(Hittable *)};
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

