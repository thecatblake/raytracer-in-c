//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_RAY_TEST_H
#define RAYTRACING_IN_C_RAY_TEST_H

#include "tests.h"

TEST(test_ray_instantiation) {
    tuple_t origin = vector(2, 3, 4);
    tuple_t direction = vector(1, 0, 0);

    ray_t r = ray(origin, direction);

    munit_assert(tuple_cmp2(origin, r.origin));
    munit_assert(tuple_cmp2(direction, r.direction));

    return MUNIT_OK;
}

TEST(test_ray_position) {
    tuple_t origin = point(2, 3, 4);
    tuple_t direction = vector(1, 0, 0);

    ray_t r = ray(origin, direction);

    munit_assert(tuple_cmp2(ray_position(&r, 2.5), point(4.5, 3, 4)));

    return MUNIT_OK;
}

#define RAY_TESTS \
    {             \
        "ray_instantiation", \
        test_ray_instantiation, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },            \
    {             \
        "ray_position", \
        test_ray_position, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }

#endif //RAYTRACING_IN_C_RAY_TEST_H
