
#include "imaging/rgb.h"
#include <imaging/ppm.h>
#include <rendering/camera.h>

#include <rendering/hittable/sphere.h>
#include <rendering/hittable/list.h>

#include <rendering/material/lambertian.h>
#include <rendering/material/metal.h>
#include <rendering/material/dielectric.h>

#include <util/random.h>

Sphere small_spheres[600];
Lambertian diffuse_materials[600];
Metal metallic_materials[600];
size_t a=0, b=0, c=0;

Hittable *objects[600];

int main() {

    Dielectric glass = {.scatter=dielectric_scatter, .ir=1.5};
    Lambertian brown = {.scatter=lambertian_scatter, .albedo={0.4, 0.2, 0.1}};
    Lambertian grey = {.scatter=lambertian_scatter, .albedo={0.5, 0.5, 0.5}};
    Metal silver = {.scatter=metal_scatter, .albedo={0.7, 0.6, 0.5}, .fuzz=0};

    Sphere big_spheres[4] = {
        {.hit=sphere_hit, .material=(Material *) &grey, .center={0, -1000, 0}, .radius=1000},
        {.hit=sphere_hit, .material=(Material *) &silver, .center={4, 1, 0}, .radius=1},
        {.hit=sphere_hit, .material=(Material *) &glass, .center={0, 1, 0}, .radius=1},
        {.hit=sphere_hit, .material=(Material *) &brown, .center={-4, 1, 0}, .radius=1},
    };

    List list = {.hit=list_hit, .objects=objects, .count=0};
    Hittable *world = (Hittable *) &list;

    list.objects[list.count++] = (Hittable *) &big_spheres[0];
    list.objects[list.count++] = (Hittable *) &big_spheres[1];
    list.objects[list.count++] = (Hittable *) &big_spheres[2];
    list.objects[list.count++] = (Hittable *) &big_spheres[3];

    for (int x = -11; x < 11; x++) {
        for (int z = -11; z < 11; z++) {
            double choose_mat = random();
            V3 center = (V3) {randrange(x, x+0.9), 0.2, z + randrange(z, z+0.9)};

            if (v3_dist(center, (V3) {4, 0.2, 0}) < 0.9) continue;

            Sphere *sphere = &small_spheres[a++];
            sphere->hit=sphere_hit;
            sphere->center=center;
            sphere->radius=0.2;

            if (choose_mat < 0.8) {
                Lambertian *material = &diffuse_materials[b++];
                material->scatter = lambertian_scatter;
                material->albedo = (RGB) {random()*random(), random()*random(), random()*random()};
                sphere->material = (Material *) material;
            }
            else if (choose_mat < 0.95) {
                Metal *material = &metallic_materials[c++];
                material->scatter = metal_scatter;
                material->albedo = rgb_from_v3(randrange_3d(0.5, 1)),
                material->fuzz = randrange(0, 0.5);
                sphere->material = (Material *) material;
            }
            else {
                sphere->material = (Material *) &glass;
            }

            list.objects[list.count++] = (Hittable *) sphere;
        }
    }

    Camera camera = {
        .image_height = 675,
        .image_width = 1200,

        .vfov = 20,
        .center = {13, 2, 3},
        .lookat = {0, 0, 0},
        .up = {0, 1, 0},

        .defocus_angle = 0.6,
        .focus_dist = 10.0,

        .samples_per_pixel = 100,
        .max_bounces = 50,
    };

    Image *image = camera_render(&camera, world);

    write_ppm(stdout, image);
}

