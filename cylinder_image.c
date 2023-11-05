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
    cylinder_data_t cyl_data = {
            .maximum = 5,
            .minimum = -5,
            .closed = 1
    };
    cylinder_init(&cylinder, &cyl_data);
    cylinder.material.color = vector(1, 0, 0);
    cylinder.material.reflective = 0.6;

    object_t right;
    cylinder_data_t right_data = {
            .maximum = 2,
            .minimum = -2,
            .closed = 1
    };
    cylinder_init(&right, &right_data);
    object_scale(&right, vector(0.5, 0.5, 0.5));
    object_translate(&right, vector(0, 0, -2));
    right.material.color = vector(0, 1, 0);

    object_t left;
    sphere_init(&left);
    object_translate(&left, vector(-4.5, 1, -1));
    object_scale(&left, vector(0.33, 0.33, 0.33));
    left.material.color = vector(0, 0, 1);
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;

    world_t world;
    world_init(&world);

    point_light_t light = {point(-3, 3, -3), vector(1, 1, 1)};
    world.light = &light;
    world_add_object(&world, &floor);
    world_add_object(&world, &cylinder);
    world_add_object(&world, &left);
    world_add_object(&world, &right);

    int width = 2000;
    int height = 2000;

    camera_t camera;
    camera_init(&camera, width, height, M_PI / 3);
    camera_transform(&camera, point(0, 1, -5), point(0, 0, 1), vector(0, 10, 0));

    int n_pixels = width * height;

    tuple_t *pixels = malloc(sizeof(tuple_t) * n_pixels);

    camera_render(&camera, &world, pixels);

    FILE *fp = fopen("cylinder_image.ppm", "w");
    canvas_write_ppm(width, height, pixels, fp);

    fclose(fp);
    free(pixels);
}