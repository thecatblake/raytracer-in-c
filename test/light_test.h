//
// Created by ryousuke kaga on 2023/10/30.
//

#ifndef RAY_TRACER_IN_C_LIGHT_TEST_H
#define RAY_TRACER_IN_C_LIGHT_TEST_H

#include "tests.h"

TEST(test_lighting_eye_between_light_surface) {
    tuple_t eyev = vector(0, 0, -1);
    tuple_t normalv = vector(0, 0, -1);
    point_light_t light = {point(0, 0, -10), vector(1, 1, 1)};
    material_t m;
    material_init(&m);
    tuple_t position = point(0, 0, 0);

    tuple_t result = lighting(&m, &light, position, eyev, normalv, 0);

    munit_assert(tuple_cmp2(result, vector(1.9, 1.9, 1.9)));

    return MUNIT_OK;
}

TEST(test_lighting_eye_between_light_surface_eye_offset) {
    tuple_t eyev = vector(0, sqrt(2)/2, -sqrt(2)/2);
    tuple_t normalv = vector(0, 0, -1);
    point_light_t light = {point(0, 0, -10), vector(1, 1, 1)};
    material_t m;
    material_init(&m);
    tuple_t position = point(0, 0, 0);

    tuple_t result = lighting(&m, &light, position, eyev, normalv, 0);
    munit_assert(tuple_cmp2(result, vector(1.0, 1.0, 1.0)));

    return MUNIT_OK;
}

TEST(test_lighting_eye_opposite_surface_light_offset) {
    tuple_t eyev = vector(0, 0, -1);
    tuple_t normalv = vector(0, 0, -1);
    point_light_t light = {point(0, 10, -10), vector(1, 1, 1)};
    material_t m;
    material_init(&m);
    tuple_t position = point(0, 0, 0);

    tuple_t result = lighting(&m, &light, position, eyev, normalv, 0);
    munit_assert(tuple_cmp2(result, vector(0.7354, 0.7364, 0.7364)));

    return MUNIT_OK;
}

TEST(test_lighting_eye_path_reflection_vector) {
    tuple_t eyev = vector(0, -sqrt(2)/2, -sqrt(2)/2);
    tuple_t normalv = vector(0, 0, -1);
    point_light_t light = {point(0, 10, -10), vector(1, 1, 1)};
    material_t m;
    material_init(&m);
    tuple_t position = point(0, 0, 0);

    tuple_t result = lighting(&m, &light, position, eyev, normalv, 0);
    munit_assert(tuple_cmp2(result, vector(1.6364, 1.6364, 1.6364)));

    return MUNIT_OK;
}

TEST(test_lighting_light_behind_surface) {
    tuple_t eyev = vector(0, 0, -1);
    tuple_t normalv = vector(0, 0, -1);
    point_light_t light = {point(0, 0, 10), vector(1, 1, 1)};
    material_t m;
    material_init(&m);
    tuple_t position = point(0, 0, 0);

    tuple_t result = lighting(&m, &light, position, eyev, normalv, 0);

    munit_assert(tuple_cmp2(result, vector(0.1, 0.1, 0.1)));

    return MUNIT_OK;
}

TEST(test_lighting_surface_in_shadow) {
    tuple_t eyev = vector(0, 0, -1);
    tuple_t normalv = vector(0, 0, -1);
    point_light_t light = {point(0, 0, -10), vector(1, 1, 1)};
    int in_shadow = 1;
    material_t m;
    material_init(&m);
    tuple_t position = point(0, 0, 0);

    tuple_t result = lighting(&m, &light, position, eyev, normalv, in_shadow);

    munit_assert(tuple_cmp2(result, vector(0.1, 0.1, 0.1)));

    return MUNIT_OK;
};

#define LIGHT_TESTS \
    {             \
        "lighting with the eye between the light and the surface", \
        test_lighting_eye_between_light_surface, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },            \
    {             \
        "lighting with eye between light and surface, eye offset 45 degrees", \
        test_lighting_eye_between_light_surface_eye_offset, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },            \
    {             \
        "lighting with eye opposite surface, light offset 45 degrees", \
        test_lighting_eye_between_light_surface_eye_offset, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },            \
    {             \
        "lighting with eye in the path of the reflection vector", \
        test_lighting_eye_path_reflection_vector, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },            \
    {             \
        "lighting with the light behind the surface", \
        test_lighting_light_behind_surface, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }



#endif //RAY_TRACER_IN_C_LIGHT_TEST_H
