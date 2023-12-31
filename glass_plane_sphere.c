//
// Created by ryousuke kaga on 2023/11/03.
//
//
// Created by ryousuke kaga on 2023/11/02.
//

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
    floor.material.reflective = 1.0;

    object_t upper_floor;
    plane_init(&upper_floor);
    upper_floor.material.pattern = check_pattern;
    upper_floor.material.reflective = 1.0;
    object_translate(&upper_floor, vector(0, 5, 0));

    object_t back_wall;
    plane_init(&back_wall);
    object_rotate_x(&back_wall, M_PI / 2);
    object_translate(&back_wall, vector(0, 0, 7));
    back_wall.material.pattern = check_pattern;

    object_t middle;
    sphere_init(&middle);
    object_translate(&middle, vector(-0.5, 1, 0.5));
    middle.material.color = vector(1, 0, 0);
    middle.material.reflective = 0.5;

    object_t right;
    sphere_init(&right);
    object_translate(&right, vector(1.5, 1, -0.5));
    object_scale(&right, vector(0.5, 0.5, 0.5));
    right.material.color = vector(0, 1, 0);
    right.material.reflective = 0.5;

    object_t left;
    sphere_init(&left);
    object_translate(&left, vector(-4.5, 1, -0.75));
    object_scale(&left, vector(0.33, 0.33, 0.33));
    left.material.color = vector(0, 0, 1);
    left.material.reflective = 0.5;

    world_t world;
    world_init(&world);

    point_light_t light = {point(-3, 3, -3), vector(1, 1, 1)};
    world.light = &light;
    world_add_object(&world, &floor);
    world_add_object(&world, &middle);
    world_add_object(&world, &left);
    world_add_object(&world, &right);

    int width = 2000;
    int height = 2000;

    camera_t camera;
    camera_init(&camera, width, height, M_PI / 3);
    camera_transform(&camera, point(0, 1, -5), point(0, 0, 1), vector(0, 1, 0));

    int n_pixels = width * height;

    tuple_t* pixels = malloc(sizeof(tuple_t) * n_pixels);

    camera_render(&camera, &world, pixels);

    FILE* fp = fopen("glass_sphere_plane_image.ppm", "w");
    canvas_write_ppm(width, height, pixels, fp);

    fclose(fp);
    free(pixels);
}