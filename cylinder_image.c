//
// Created by ryousuke kaga on 2023/11/05.
//

#include <stdlib.h>
#include <stdio.h>
#include "tuple.h"
#include "object.h"
#include "ray.h"
#include "canvas.h"
#include "light.h"
#include "world.h"
#include "camera.h"
#include "plane.h"

int main() {
    stripe_pattern_t stripe = {vector(0, 0, 0), vector(1, 1, 1)};
    pattern_t stripe_pattern;
    stripe_init(&stripe_pattern, &stripe);

    stripe_pattern_t gradient = {vector(0.1803, 0.1921, 0.572549), vector(0.1058, 1, 1)};
    pattern_t gradient_pattern;
    gradient_init(&gradient_pattern, &gradient);
    transform_translate(&gradient_pattern.transform, vector(0, 0, 1));

    stripe_pattern_t check = {vector(0, 0, 0), vector(1, 1, 1)};
    pattern_t check_pattern;
    check_init(&check_pattern, &check);
    transform_scale(&check_pattern.transform, vector(0.2, 0.2, 0.2));

    object_t floor;
    plane_init(&floor);
    floor.material.pattern = check_pattern;
    floor.material.reflective = 0.5;

    object_t cylinder;
    cylinder_init(&cylinder);
    cylinder.material.color = vector(0.6, 0.9, 0.6);

    world_t world;
    world_init(&world);

    point_light_t light = {point(-3, 3, -3), vector(1, 1, 1)};
    world.light = &light;
    world_add_object(&world, &floor);
    world_add_object(&world, &cylinder);

    int width = 2000;
    int height = 2000;

    camera_t camera;
    camera_init(&camera, width, height, M_PI / 3);
    camera_transform(&camera, point(0, 1, -15), point(0, 8, 1), vector(0, 10, 0));

    int n_pixels = width * height;

    tuple_t *pixels = malloc(sizeof(tuple_t) * n_pixels);

    camera_render(&camera, &world, pixels);

    FILE *fp = fopen("cylinder_image.ppm", "w");
    canvas_write_ppm(width, height, pixels, fp);

    fclose(fp);
    free(pixels);
}