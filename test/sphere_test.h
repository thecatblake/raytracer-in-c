//
// Created by ryousuke kaga on 2023/09/26.
//

#ifndef RAYTRACING_IN_C_SPHERE_TEST_H
#define RAYTRACING_IN_C_SPHERE_TEST_H

#include "tests.h"

TEST(test_sphere_hit) {
    ray_t ray = ray(point(-2, -2, 0), vector(1, 1, 0));
    object_t sphere;
    object_init(&sphere);

    double buf[2];
    int hit_num;
    sphere_hit(&ray, buf, &hit_num);

    munit_assert(hit_num == 2);
    munit_assert(tuple_cmp2(ray_position(&ray, buf[0]), point(cos(M_PI/4 * 5), sin(M_PI/4 * 5), 0)));
    munit_assert(tuple_cmp2(ray_position(&ray, buf[1]), point(cos(M_PI/4), sin(M_PI/4), 0)));

    return MUNIT_OK;
}

#define SPHERE_TESTS \
    {                \
        "sphere_hit", \
        test_sphere_hit, \
        NULL,        \
        NULL,        \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }

#endif //RAYTRACING_IN_C_SPHERE_TEST_H
