
#include <imaging/ppm.h>
#include <rendering/camera.h>

#include <rendering/hittable/sphere.h>
#include <rendering/hittable/list.h>

#include <rendering/material/lambertian.h>
#include <rendering/material/metal.h>
#include <rendering/material/dielectric.h>


int main() {
    Lambertian ground_material_ = {
        .scatter=lambertian_scatter,
        .albedo={0.8, 0.8, 0.0},
    };
    Lambertian center_material_ = {
        .scatter=lambertian_scatter,
        .albedo={0.1, 0.2, 0.5},
    };
    Dielectric left_material_ = {
        .scatter=dielectric_scatter,
        .ir=1.5,
    };
    Metal right_material_ = {
        .scatter=metal_scatter,
        .albedo={0.8, 0.6, 0.2},
        .fuzz=0,
    };

    Material *ground_material = (Material *) &ground_material_;
    Material *center_material = (Material *) &center_material_;
    Material *left_material = (Material *) &left_material_;
    Material *right_material = (Material *) &right_material_;

    Sphere ground = {
        .hit=sphere_hit, .material=ground_material, .center={0, -100.5, -1}, .radius=100,
    };
    Sphere center_ball = {
        .hit=sphere_hit, .material=center_material, .center={0, 0, -1}, .radius=0.5
    };
    Sphere left_ball_outer = {
        .hit=sphere_hit, .material=left_material, .center={-1, 0, -1}, .radius=0.5
    };
    Sphere left_ball_inner = {
        .hit=sphere_hit, .material=left_material, .center={-1, 0, -1}, .radius=-0.4
    };
    Sphere right_ball = {
        .hit=sphere_hit, .material=right_material, .center={1, 0, -1}, .radius=0.5
    };

    Hittable *objects[] = {
        (Hittable *) &ground,
        (Hittable *) &center_ball,
        (Hittable *) &left_ball_outer,
        (Hittable *) &left_ball_inner,
        (Hittable *) &right_ball
    };
    List object_list = {.hit=list_hit, .objects=objects, .count=5};
    Hittable *world = (Hittable *) &object_list;

    Camera camera = {
        .image_height = 450,
        .image_width = 800,
        .center = {-2, 2, 1},
        .lookat = {0, 0, -1},
        .up = {0, 1, 0},
        .vfov = 20,
        .samples_per_pixel = 100,
        .max_bounces = 50,
        .defocus_angle = 10,
        .focus_dist = 3.4,
    };

    Image *image = camera_render(&camera, world);

    write_ppm(stdout, image);
}

