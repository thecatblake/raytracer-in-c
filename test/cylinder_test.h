//
// Created by ryousuke kaga on 2023/11/05.
//

#ifndef RAY_TRACER_IN_C_CYLINDER_TEST_H
#define RAY_TRACER_IN_C_CYLINDER_TEST_H

#include "tests.h"

TEST(test_ray_misses_cylinder) {
    object_t cyl;
    cylinder_init(&cyl, NULL);

    tuple_t origins[] = {
        point(1, 0, 0),
        point(0, 0, 0),
        point(0, 0, -5)
    };

    tuple_t directions[] = {
            vector(0, 1, 0),
            vector(0, 1, 0),
            vector(1, 1, 1)
    };

    for (int i=0; i < 3; i++) {
        ray_t ray = {origins[i], directions[i]};

        double hits[2];
        int hit_num;
        cylinder_hit(&cyl, &ray, hits, &hit_num);

        munit_assert(hit_num == 0);
    }

    return MUNIT_OK;
}

TEST(test_ray_strikes_cylinder) {
    object_t cyl;
    cylinder_init(&cyl, NULL);

    tuple_t origins[] = {
            point(1, 0, -5),
            point(0, 0, -5),
            point(0.5, 0, -5)
    };

    tuple_t directions[] = {
            vector(0, 0, 1),
            vector(0, 0, 1),
            vector(0.1, 1, 1)
    };

    double ts[][2] = {
            {5, 5},
            {4, 6},
            {6.80798, 7.08872}
    };

    for (int i=0; i < 3; i++) {
        ray_t ray = {origins[i], directions[i]};

        double hits[2];
        int hit_num;
        cylinder_hit(&cyl, &ray, hits, &hit_num);

        munit_assert(hit_num == 2);
        munit_assert(double_cmp2(hits[0], ts[i][0]));
        munit_assert(double_cmp2(hits[1], ts[i][1]));
    }

    return MUNIT_OK;
}

TEST(test_normal_vector_on_cylinder) {
    object_t cyl;
    cylinder_init(&cyl, NULL);

    tuple_t points[] = {
            point(1, 0, 0),
            point(0, 5, -1),
            point(0, -2, 1),
            point(-1, 1, 0)
    };

    tuple_t normals[] = {
            vector(1, 0, 0),
            vector(0, 0,-1),
            vector(0, 0, 1),
            vector(-1, 0, 0)
    };

    for (int i=0; i < 4; i++) {
        tuple_t n = cylinder_normal_at(&cyl, points[i]);

        munit_assert(tuple_cmp2(n, normals[i]));
    }

    return MUNIT_OK;
}

TEST(test_intersect_constrained_cylinder) {
    object_t cylinder;
    cylinder_data_t data = {
            .minimum = 1,
            .maximum = 2
    };
    cylinder_init(&cylinder, &data);

    tuple_t origins[] = {
            point(0, 1.5, 0),
            point(0, -3, -5),
            point(0, 0, -5),
            point(0, 2, -5),
            point(0, 1, -5),
            point(0, 1.5, -2)
    };

    tuple_t directions[] = {
            vector(0.1, 1, 0),
            vector(0, 0, 1),
            vector(0, 0, 1),
            vector(0, 0, 1),
            vector(0, 0, 1),
            vector(0, 0, 1)
    };

    int counts[] = {
            0,
            0,
            0,
            0,
            0,
            2
    };

    for(int i=0; i < 6; i++) {
        ray_t ray = {origins[i],directions[i]};
        double hits[2];
        int hit_num;
        cylinder_hit(&cylinder, &ray, hits, &hit_num);

        munit_assert(hit_num == counts[i]);
    }

    return MUNIT_OK;
};

#define CYLINDER_TESTS \
    {             \
        "A ray misses a cylinder", \
        test_ray_misses_cylinder, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },            \
    {             \
        "A ray strikes a cylinder", \
        test_ray_position, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },                 \
    {             \
        "Normal vector on a cylinder", \
        test_normal_vector_on_cylinder, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },                 \
    {             \
        "Intersecting a constrained cylinder", \
        test_intersect_constrained_cylinder, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }

#endif //RAY_TRACER_IN_C_CYLINDER_TEST_H
