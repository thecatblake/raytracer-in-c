//
// Created by ryousuke kaga on 2023/10/31.
//

#ifndef RAY_TRACER_IN_C_CAMERA_TEST_H
#define RAY_TRACER_IN_C_CAMERA_TEST_H

#include "tests.h"

TEST(test_pixel_size_horizontal_canvas) {
    camera_t camera;
    camera_init(&camera, 200, 125, M_PI/2);

    munit_assert(double_cmp2(camera.pixel_size, 0.01));

    return MUNIT_OK;
}

TEST(test_pixel_size_vertical_canvas) {
    camera_t camera;
    camera_init(&camera, 125, 200, M_PI/2);

    munit_assert(double_cmp2(camera.pixel_size, 0.01));

    return MUNIT_OK;
}

TEST(test_construct_ray_through_center) {
    camera_t camera;
    camera_init(&camera, 201, 101, M_PI/2);
    ray_t ray = ray_for_pixel(&camera, 100, 50);

    munit_assert(tuple_cmp2(ray.origin, point(0, 0, 0)));
    munit_assert(tuple_cmp2(ray.direction, vector(0, 0, -1)));

    return MUNIT_OK;
}

TEST(test_construct_ray_through_corner) {
    camera_t camera;
    camera_init(&camera, 201, 101, M_PI/2);
    ray_t ray = ray_for_pixel(&camera, 0, 0);

    munit_assert(tuple_cmp2(ray.origin, point(0, 0, 0)));
    munit_assert(tuple_cmp2(ray.direction, vector(0.66519, 0.33259, -0.66851)));

    return MUNIT_OK;
}

TEST(test_construct_ray_when_camera_transformed) {
    camera_t camera;
    camera_init(&camera, 201, 101, M_PI/2);
    matrix_t temp;
    add_transform(camera.transform, *rotation_y_matrix(M_PI / 4, &temp), &camera.transform);
    add_transform(camera.transform, *translation_matrix(0, -2, 5, &temp), &camera.transform);
    ray_t ray = ray_for_pixel(&camera, 100, 50);

    munit_assert(tuple_cmp2(ray.origin, point(0, 2, -5)));
    munit_assert(tuple_cmp2(ray.direction, vector(sqrt(2)/2, 0, -sqrt(2)/2)));

    return MUNIT_OK;
}

TEST(test_render_world_with_camera) {
    world_t world;
    world_init(&world);

    point_light_t light = {point(-10, 10, -10), vector(1, 1, 1)};
    world.light = &light;

    object_t s1;
    sphere_init(&s1);
    s1.type_name = SPHERE;
    material_t material;
    material_init(&material);
    material.color = vector(0.8, 1.0, 0.6);
    material.diffuse = 0.7;
    material.specular = 0.2;
    s1.material = material;

    object_t s2;
    sphere_init(&s2);
    s2.type_name = SPHERE;
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    camera_t camera;
    camera_init(&camera, 11, 11, M_PI / 2);
    camera_transform(&camera, point(0, 0, -5), point(0, 0, 0), vector(0, 1, 0));

    tuple_t* pixels = malloc(sizeof(tuple_t) * 11 * 11);

    camera_render(&camera, &world, pixels);
    munit_assert(tuple_cmp2(pixel_at(11, pixels, 5, 5), vector(0.38066, 0.47583, 0.2855)));

    return MUNIT_OK;
}


#define CAMERA_TESTS \
    {             \
        "The pixel size for horizontal canvas", \
        test_pixel_size_horizontal_canvas, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },            \
    {             \
        "The pixel size for vertical canvas", \
        test_pixel_size_vertical_canvas, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },               \
    {             \
        "Constructing a ray through the center of the canvas", \
        test_construct_ray_through_center, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },               \
    {             \
        "Constructing a ray through the corner of the canvas", \
        test_construct_ray_through_corner, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },               \
    {             \
        "Constructing a ray when the camera is transformed", \
        test_construct_ray_when_camera_transformed, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },               \
    {             \
        "rendering a world with a camera", \
        test_render_world_with_camera, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }


#endif //RAY_TRACER_IN_C_CAMERA_TEST_H
