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

int main() {
    int width = 1800;
    int height = 1800;
    int n_pixels = width * height;

    tuple_t* pixels = malloc(sizeof(tuple_t) * n_pixels);

    object_t sphere;
    object_init(&sphere);

    object_scale(&sphere, vector(200, 200, 200));
    object_translate(&sphere, vector(500, 500, 0));

    tuple_t origin = point(0, 0, -4000);

    tuple_t left_top = point(-width / 2.0, height / 2.0, 0.0);

    canvas_fill(width, height, pixels, point(0, 0, 0));

    // calculate pixels from left top to right bottom
    for (int i=0; i < n_pixels; i++) {
        int y = (int)left_top.y - i / width;
        int x = (int)left_top.x + i % width;
        //printf("x: %d, y: %d\n", x, y);

        ray_t ray;
        ray.origin = origin;
        ray.direction = tuple_norm(vector(x - ray.origin.x, y - ray.origin.y, -ray.origin.z));
        matrix_t origin_inv, direction_inv;
        matrix_inv(sphere.origin_transform, &origin_inv);
        matrix_inv(sphere.direction_transform, &direction_inv);
        ray.origin = tuple_transform(origin_inv, ray.origin);
        ray.direction = tuple_transform(direction_inv, ray.direction);

        double hits[2];
        int hit_num;
        sphere_hit(&ray, hits, &hit_num);

        if (hit_num > 0) {
            pixels[i] = point(1, 0, 0);
        }
    }

    FILE* fp = fopen("sphere_image.ppm", "w");
    canvas_write_ppm(width, height, pixels, fp);
}