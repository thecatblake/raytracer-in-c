//
// Created by ryousuke kaga on 2023/11/04.
//

#ifndef RAY_TRACER_IN_C_CUBE_TEST_H
#define RAY_TRACER_IN_C_CUBE_TEST_H

#include "tests.h"

TEST(test_ray_intersect_cube) {
    object_t cube;
    cube_init(&cube);

    tuple_t origins[] = {
            point(5, 0.5, 0),
            point(-5, 0.5, 0),
            point(0.5, 5, 0),
            point(0.5, -5, 0),
            point(0.5, 0, 5),
            point(0.5, 0, -5),
            point(0, 0.5, 0)
    };

    tuple_t directions[] = {
            vector(-1, 0, 0),
            vector(1, 0, 0),
            vector(0, -1, 0),
            vector(0, 1, 0),
            vector(0, 0, -1),
            vector(0, 0, 1),
            vector(0, 0, 1)
    };

    double ts[][2] = {
            {4, 6},
            {4, 6},
            {4, 6},
            {4, 6},
            {4, 6},
            {4, 6},
            {-1, 1}
    };

    for (int i=0; i < 7; i++) {
        ray_t ray = {origins[i], directions[i]};
        double hits[2];
        int hit_num;
        cube_hit(&ray, hits, &hit_num);

        munit_assert(hit_num == 2);
        munit_assert(double_cmp2(hits[0], ts[i][0]));
        munit_assert(double_cmp2(hits[1], ts[i][1]));
    }

    return MUNIT_OK;
}

TEST(test_ray_misses_cube) {
    object_t cube;
    cube_init(&cube);

    tuple_t origins[] = {
            point(-2, 0, 0),
            point(0, -2, 0),
            point(0, 0, -2),
            point(2, 0, 2),
            point(0, 2, 2),
            point(2, 2, 0)
    };

    tuple_t directions[] = {
            vector(0.2673, 0.5345, 0.8018),
            vector(0.8018, 0.2673, 0.5345),
            vector(0.5345, 0.8018, 0.2673),
            vector(0, 0, -1),
            vector(0, -1, 0),
            vector(-1, 0, 0)
    };

    for (int i=0; i < 6; i++) {
        ray_t ray = {origins[i], directions[i]};
        double hits[2];
        int hit_num;
        cube_hit(&ray, hits, &hit_num);

        munit_assert(hit_num == 0);
    }

    return MUNIT_OK;
}

TEST(test_normal_on_surface_of_cube) {
    object_t cube;
    cube_init(&cube);

    tuple_t points[] = {
        point(1, 0.5, -0.8),
        point(-1, -0.2, 0.9),
        point(-0.4, 1, -0.1),
        point(0.3, -1, -0.7),
        point(-0.6, 0.3, 1),
        point(0.4, 0.4, -1),
        point(1, 1, 1),
        point(-1, -1, -1)
    };

    tuple_t normals[] = {
            vector(1, 0, 0),
            vector(-1, 0, 0),
            vector(0, 1, 0),
            vector(0, -1, 0),
            vector(0, 0, 1),
            vector(0, 0, -1),
            vector(1, 0, 0),
            vector(-1, 0, 0)
    };

    for(int i=0; i < 8; i++) {
        tuple_t normal = cube_normal_at(&cube, points[i]);

        munit_assert(tuple_cmp2(normal, normals[i]));
    }

    return MUNIT_OK;
}

#define CUBE_TESTS \
    {             \
        "A ray intersects a cube", \
        test_ray_intersect_cube, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },             \
    {             \
        "A ray misses a cube", \
        test_ray_misses_cube, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },             \
    {             \
        "The normal on the surface of a cube", \
        test_normal_on_surface_of_cube, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }

#endif //RAY_TRACER_IN_C_CUBE_TEST_H
