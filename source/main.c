
#include <imaging/ppm.h>
#include <rendering/camera.h>

#include <rendering/hittable/sphere.h>
#include <rendering/hittable/list.h>

#include <rendering/material/lambertian.h>
#include <rendering/material/metal.h>
#include <rendering/material/dielectric.h>


int main() {
    Metal silver_ = {
        .scatter=metal_scatter,
        .albedo={0.9, 0.9, 0.9},
        .fuzz=0.1,
    };
    Metal diffuse_red_ = {
        .scatter=lambertian_scatter,
        .albedo={1, 0, 0},
        .fuzz=0.05,
    };
    Lambertian diffuse_grey_ = {
        .scatter=lambertian_scatter,
        .albedo={0.5, 0.5, 0.5},
    };

    Material *silver = (Material *) &silver_;
    Material *diffuse_red = (Material *) &diffuse_red_;
    Material *diffuse_grey = (Material *) &diffuse_grey_;

    Sphere blue_ball = {.hit=sphere_hit, .material=silver, .center={-1, 1, -1}, .radius=1};
    Sphere red_ball = {.hit=sphere_hit, .material=diffuse_red, .center={+1, 1, -1}, .radius=1};
    Sphere ground = {.hit=sphere_hit, .material=diffuse_grey, .center={0, -500, -1}, .radius=500};

    Hittable *objects[] = {(Hittable *) &red_ball, (Hittable *) &blue_ball, (Hittable *) &ground};
    List object_list = {.hit=list_hit, .objects=objects, .count=3};
    Hittable *world = (Hittable *) &object_list;

    Camera camera = {
        .image_height = 450,
        .image_width = 800,
        .center = {3, 1, 2},
        .lookat = {0, 1, -1},
        .up = {1, 1, 0},
        .vfov = 40,
        .samples_per_pixel = 100,
        .max_bounces = 50,
    };

    Image *image = camera_render(&camera, world);

    write_ppm(stdout, image);
}

