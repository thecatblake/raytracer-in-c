//
// Created by ryousuke kaga on 2023/10/26.
//
#include <stdlib.h>
#include <stdio.h>
#include "tuple.h"
#include "object.h"
#include "ray.h"
#include "canvas.h"
#include "light.h"
#include "world.h"

int main() {
    int width = 2500;
    int height = 2500;
    int n_pixels = width * height;

    tuple_t* pixels = malloc(sizeof(tuple_t) * n_pixels);

    object_t s1;
    object_init(&s1);
    s1.type_name = SPHERE;
    object_scale(&s1, vector(300, 300, 300));
    object_translate(&s1, vector(-500, 0, 0));
    material_t material;
    material_init(&material);
    material.color = vector(1, 0.2, 1);
    s1.material = material;

    object_t s2;
    object_init(&s2);
    s2.type_name = SPHERE;
    object_scale(&s2, vector(300, 300, 300));
    object_translate(&s2, vector(100, 0, 0));
    s2.material = material;
    s2.material.color = vector(0.2, 1, 1);

    object_t s3;
    object_init(&s3);
    s3.type_name = SPHERE;
    object_scale(&s3, vector(300, 300, 300));
    object_translate(&s3, vector(800, 0, 0));
    s3.material = material;
    s3.material.color = vector(1, 1, 0.2);

    point_light_t light = {point(-1000, 1000, -1000), vector(1, 1, 1)};

    world_t world;
    world_init(&world);
    world_add_object(&world, &s1);
    world_add_object(&world, &s2);
    world_add_object(&world, &s3);
    world.light = &light;

    tuple_t origin = point(0, 0, -4000);

    tuple_t left_top = point(-width / 2.0, height / 2.0, 0.0);

    canvas_fill(width, height, pixels, point(0, 0, 0));

    // calculate pixels from left top to right bottom
    for (int i=0; i < n_pixels; i++) {
        int y = (int)left_top.y - i / width;
        int x = (int)left_top.x + i % width;

        ray_t ray;

        ray.origin = origin;
        ray.direction = tuple_norm(vector(x - ray.origin.x, y - ray.origin.y, -ray.origin.z));

        tuple_t color = color_at(&world, &ray);

        pixels[i] = color;
    }

    FILE* fp = fopen("sphere_image.ppm", "w");
    canvas_write_ppm(width, height, pixels, fp);
}