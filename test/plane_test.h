//
// Created by ryousuke kaga on 2023/11/02.
//

#ifndef RAY_TRACER_IN_C_PLANE_TEST_H
#define RAY_TRACER_IN_C_PLANE_TEST_H

#include "tests.h"

TEST(test_plane_normal_constant) {
    object_t plane;
    plane_init(&plane);
    tuple_t n1, n2, n3;
    n1 = plane_normal_at(&plane, point(0, 0, 0));
    n2 = plane_normal_at(&plane, point(10, 0, -10));
    n3 = plane_normal_at(&plane, point(-5, 0, 150));

    munit_assert(tuple_cmp2(n1, point(0, 1, 0)));
    munit_assert(tuple_cmp2(n2, point(0, 1, 0)));
    munit_assert(tuple_cmp2(n3, point(0, 1, 0)));

    return MUNIT_OK;
}

TEST(test_intersect_ray_parallel) {
    object_t plane;
    plane_init(&plane);
    ray_t ray = {point(0, 10, 0), vector(0, 0, 1)};
    double buf[1];
    int hit_num;
    plane_hit(&ray, buf, &hit_num);

    munit_assert(hit_num == 0);

    return MUNIT_OK;
}

TEST(test_ray_intersecting_plane_above) {
    object_t plane;
    plane_init(&plane);
    ray_t ray = {point(0, 1, 0), vector(0, -1, 0)};
    double buf[1];
    int hit_num;
    plane_hit(&ray, buf, &hit_num);

    munit_assert(hit_num == 1);
    munit_assert(buf[0] == 1);

    return MUNIT_OK;
}


#define PLANE_TESTS \
    {             \
        "The normal of a plane is constant everywhere", \
        test_plane_normal_constant, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {             \
        "Intersect with a ray parallel to the plane", \
        test_intersect_ray_parallel, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {             \
        "A ray intersecting a plane from above", \
        test_ray_intersecting_plane_above, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }

#endif //RAY_TRACER_IN_C_PLANE_TEST_H
