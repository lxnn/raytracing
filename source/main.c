
#include <imaging/ppm.h>
#include <rendering/camera.h>

#include <rendering/hittable/sphere.h>
#include <rendering/hittable/list.h>

#include <rendering/material/lambertian.h>
#include <rendering/material/metal.h>
#include <rendering/material/dielectric.h>


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
        .fuzz=0.3,
    };
    Metal gold_ = {
        .scatter=metal_scatter,
        .albedo={0.8, 0.6, 0.2},
        .fuzz=1.0,
    };
    Dielectric glass_ = {
        .scatter=dielectric_scatter,
        .ir=1.5,
    };

    Material *diffuse_grey = (Material *) &diffuse_grey_;
    Material *diffuse_yellow = (Material *) &diffuse_yellow_;
    Material *silver = (Material *) &silver_;
    Material *gold = (Material *) &gold_;
    Material *glass = (Material *) &glass_;

    Sphere spheres[] = {
        {.hit=sphere_hit, .material=glass, .center={0, 0, -1}, .radius=0.5},
        {.hit=sphere_hit, .material=diffuse_yellow, .center={0, -100.5, -1}, .radius=100},
        {.hit=sphere_hit, .material=glass, .center={-1, 0, -1}, .radius=0.5},
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
        .center = {0, 0, 0},
        .focal_length = 1.0,
        .viewport_height = 2.0,
        .samples_per_pixel = 100,
        .max_bounces = 50,
    };

    Image *image = camera_render(&camera, world);

    write_ppm(stdout, image);
}

