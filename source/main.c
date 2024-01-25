
#include <imaging/ppm.h>
#include <rendering/camera.h>

#include <rendering/hittable/sphere.h>
#include <rendering/hittable/list.h>

#include <rendering/material/lambertian.h>
#include <rendering/material/metal.h>
#include <rendering/material/dielectric.h>


int main() {
    Lambertian diffuse_red_ = {
        .scatter=lambertian_scatter,
        .albedo={1, 0, 0},
    };
    Lambertian diffuse_blue_ = {
        .scatter=lambertian_scatter,
        .albedo={0, 0, 1},
    };

    Material *diffuse_red = (Material *) &diffuse_red_;
    Material *diffuse_blue = (Material *) &diffuse_blue_;

    double r = 0.70711;
    Sphere blue_ball = {.hit=sphere_hit, .material=diffuse_blue, .center={-r, 0, -1}, .radius=r};
    Sphere red_ball = {.hit=sphere_hit, .material=diffuse_red, .center={+r, 0, -1}, .radius=r};

    Hittable *objects[] = {(Hittable *) &red_ball, (Hittable *) &blue_ball};
    List object_list = {.hit=list_hit, .objects=objects, .count=2};
    Hittable *world = (Hittable *) &object_list;

    Camera camera = {
        .image_height = 450,
        .image_width = 800,
        .center = {0, 0, 0},
        .focal_length = 1.0,
        .vfov = 90,
        .samples_per_pixel = 100,
        .max_bounces = 50,
    };

    Image *image = camera_render(&camera, world);

    write_ppm(stdout, image);
}

