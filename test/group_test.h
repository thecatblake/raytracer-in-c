//
// Created by ryousuke kaga on 2023/11/06.
//

#ifndef RAY_TRACER_IN_C_GROUP_TEST_H
#define RAY_TRACER_IN_C_GROUP_TEST_H

#include "tests.h"

TEST(test_group_iontersect) {
    List objects;
    list_init(&objects, NULL);
    group_data_t data = {&objects};
    object_t group;
    group_init(&group, &data);
    object_t s1;
    sphere_init(&s1);
    object_t s2;
    sphere_init(&s2);
    object_translate(&s2, vector(0, 0, -3));
    object_t s3;
    sphere_init(&s3);
    object_translate(&s3, vector(5, 0, 0));
    group_add_object(&group, &s1);
    group_add_object(&group, &s2);
    group_add_object(&group, &s3);

    ray_t ray = {point(0, 0, -5), vector(0, 0, 1)};
    intersection_t hits[6];
    int hit_num;
    group_hit(&group, &ray, hits, &hit_num);
    munit_assert(hit_num == 4);

    list_destroy(&objects);

    return MUNIT_OK;
}

TEST(test_convert_point_from_world_to_object_space) {
    List objects1;
    list_init(&objects1, NULL);
    group_data_t data = {&objects1};
    object_t g1;
    group_init(&g1, &data);
    object_rotate_y(&g1, M_PI/2);
    List objects2;
    list_init(&objects2, NULL);
    group_data_t data2 = {&objects2};
    object_t g2;
    group_init(&g2, &data2);
    object_scale(&g2, vector(2, 2, 2));
    object_t s;
    sphere_init(&s);
    object_translate(&s, vector(5, 0, 0));
    group_add_object(&g1, &g2);
    group_add_object(&g2, &s);

    tuple_t p = world_to_object(&s, point(-2, 0, -10));

    munit_assert(tuple_cmp2(p, point(0, 0, -1)));

    return MUNIT_OK;
}

TEST(test_convert_normal_from_object_to_world_space) {
    List objects1;
    list_init(&objects1, NULL);
    group_data_t data = {&objects1};
    object_t g1;
    group_init(&g1, &data);
    object_rotate_y(&g1, M_PI/2);
    List objects2;
    list_init(&objects2, NULL);
    group_data_t data2 = {&objects2};
    object_t g2;
    group_init(&g2, &data2);
    object_scale(&g2, vector(1, 2, 3));
    object_t s;
    sphere_init(&s);
    object_translate(&s, vector(5, 0, 0));
    group_add_object(&g1, &g2);
    group_add_object(&g2, &s);

    tuple_t p = normal_to_world(&s, point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));

    munit_assert(tuple_cmp2(p, vector(0.2857, 0.4286, -0.8571)));

    return MUNIT_OK;
}

TEST(test_find_normal_on_child_object) {
    List objects1;
    list_init(&objects1, NULL);
    group_data_t data = {&objects1};
    object_t g1;
    group_init(&g1, &data);
    object_rotate_y(&g1, M_PI/2);
    List objects2;
    list_init(&objects2, NULL);
    group_data_t data2 = {&objects2};
    object_t g2;
    group_init(&g2, &data2);
    object_scale(&g2, vector(1, 2, 3));
    object_t s;
    sphere_init(&s);
    object_translate(&s, vector(5, 0, 0));
    group_add_object(&g1, &g2);
    group_add_object(&g2, &s);

    tuple_t p = normal_at(&s, point(1.7321, 1.1547, -5.5774));
    tuple_print(p);
    munit_assert(tuple_cmp2(p, vector(0.2857, 0.4286, -0.8571)));

    return MUNIT_OK;
}

#define GROUP_TESTS \
    {             \
        "Intersect a ray with a group", \
        test_group_iontersect, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {             \
        "Converting a point from world to object space", \
        test_convert_point_from_world_to_object_space, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {             \
        "Converting a normal from object to world space", \
        test_convert_normal_from_object_to_world_space, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {             \
        "Finding the normal on a child object", \
        test_find_normal_on_child_object, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }

#endif //RAY_TRACER_IN_C_GROUP_TEST_H
