//
// Created by ryousuke kaga on 2023/10/26.
//
#include <stdlib.h>
#include <stdio.h>
#include "tuple.h"
#include "object.h"
#include "ray.h"
#include "sphere.h"
#include "canvas.h"
#include "light.h"

int main() {
    int width = 1000;
    int height = 1000;
    int n_pixels = width * height;

    tuple_t* pixels = malloc(sizeof(tuple_t) * n_pixels);

    object_t sphere;
    object_init(&sphere);

    object_scale(&sphere, vector(200, 200, 200));

    material_t material;
    material_init(&material);
    material.color = vector(1, 0.2, 1);
    sphere.material = material;

    point_light_t light = {point(-400, 400, -400), vector(1, 1, 1)};

    tuple_t origin = point(0, 0, -4000);

    tuple_t left_top = point(-width / 2.0, height / 2.0, 0.0);

    canvas_fill(width, height, pixels, point(0, 0, 0));

    // calculate pixels from left top to right bottom
    for (int i=0; i < n_pixels; i++) {
        int y = (int)left_top.y - i / width;
        int x = (int)left_top.x + i % width;
        //printf("x: %d, y: %d\n", x, y);

        ray_t ray_original, ray_inv;

        ray_original.origin = origin;
        ray_original.direction = tuple_norm(vector(x - ray_original.origin.x, y - ray_original.origin.y, -ray_original.origin.z));

        matrix_t origin_inv, direction_inv;
        matrix_inv(sphere.origin_transform, &origin_inv);
        matrix_inv(sphere.direction_transform, &direction_inv);
        ray_inv.origin = tuple_transform(origin_inv, ray_original.origin);
        ray_inv.direction = tuple_transform(direction_inv, ray_original.direction);

        double hits[2];
        int hit_num;
        sphere_hit(&ray_inv, hits, &hit_num);

        if (hit_num > 0) {
            tuple_t position = ray_position(&ray_original, hits[0]);
            tuple_t normalv = sphere_normal_at(&sphere, position);
            tuple_t eyev = ray_original.direction;
            tuple_t color = lighting(&sphere.material, &light, position, eyev, normalv);

            pixels[i] = color;
        }
    }

    FILE* fp = fopen("sphere_image.ppm", "w");
    canvas_write_ppm(width, height, pixels, fp);
}