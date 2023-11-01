//
// Created by ryousuke kaga on 2023/10/31.
//

#ifndef RAY_TRACER_IN_C_WORLD_TEST_H
#define RAY_TRACER_IN_C_WORLD_TEST_H

#include "tests.h"

TEST(test_world_intersection) {
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

    ray_t ray = {point(0, 0, -5), vector(0, 0, 1)};
    Heap intersections = world_intersect(&world, &ray);

    munit_assert(intersections.size == 2);

    intersection_t* intersection;

    heap_extract(&intersections, (void**)&intersection);
    munit_assert(double_cmp2(intersection->t, 4.0));

    heap_extract(&intersections, (void**)&intersection);
    munit_assert(double_cmp2(intersection->t, 4.5));

    return MUNIT_OK;
}

TEST(test_hit_occur_outside) {
    world_t world;
    world_init(&world);

    ray_t ray = {point(0, 0, -5), vector(0, 0, 1)};
    object_t sphere;
    sphere_init(&sphere);
    sphere.type_name = SPHERE;

    world_add_object(&world, &sphere);

    Heap intersections = world_intersect(&world, &ray);

    munit_assert(intersections.size == 1);

    intersection_t* intersection;
    heap_extract(&intersections, (void**)&intersection);

    computation_t computation = prepare_computation(intersection, &ray);

    munit_assert_false(computation.inside);

    return MUNIT_OK;
}

TEST(test_hit_occur_inside) {
    world_t world;
    world_init(&world);

    ray_t ray = {point(0, 0, 0), vector(0, 0, 1)};
    object_t sphere;
    sphere_init(&sphere);
    sphere.type_name = SPHERE;

    world_add_object(&world, &sphere);

    Heap intersections = world_intersect(&world, &ray);

    munit_assert(intersections.size == 1);

    intersection_t* intersection;
    heap_extract(&intersections, (void**)&intersection);

    computation_t computation = prepare_computation(intersection, &ray);

    munit_assert(tuple_cmp2(computation.position, point(0, 0, 1)));
    munit_assert(tuple_cmp2(computation.eyev, vector(0, 0, -1)));
    munit_assert(tuple_cmp2(computation.normalv, vector(0, 0, -1)));
    munit_assert(computation.inside);

    return MUNIT_OK;
}

TEST(test_shade_intersectoin) {
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

    ray_t ray = {point(0, 0, -5), vector(0, 0, 1)};
    Heap intersections = world_intersect(&world, &ray);
    intersection_t* intersection;
    heap_extract(&intersections, (void**)&intersection);
    computation_t computation = prepare_computation(intersection, &ray);
    tuple_t color = shade_hit(&world, &computation);
    munit_assert(tuple_cmp2(color, vector(0.38066, 0.47582, 0.2855)));

    return MUNIT_OK;
};

TEST(test_shade_intersectoin_inside) {
    world_t world;
    world_init(&world);

    point_light_t light = {point(0, 0.25, 0), vector(1, 1, 1)};
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

    ray_t ray = {point(0, 0, 0 ), vector(0, 0, 1)};
    Heap intersections = world_intersect(&world, &ray);

    munit_assert(intersections.size == 2);

    intersection_t* intersection;
    heap_extract(&intersections, (void**)&intersection);
    munit_assert(double_cmp2(intersection->t, 0.5));

    computation_t computation = prepare_computation(intersection, &ray);
    tuple_t color = shade_hit(&world, &computation);
    munit_assert(tuple_cmp2(color, vector(0.90498, 0.90498, 0.90498)));

    return MUNIT_OK;
};

TEST(test_color_ray_misses) {
    world_t world;
    world_init(&world);

    point_light_t light = {point(0, 0.25, 0), vector(1, 1, 1)};
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

    ray_t ray = {point(0, 0, -5), vector(0, 1, 0)};
    tuple_t color = color_at(&world, &ray);
    munit_assert(tuple_cmp2(color, vector(0, 0, 0)));

    return MUNIT_OK;
};

TEST(test_color_ray_hits) {
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

    ray_t ray = {point(0, 0, -5), vector(0, 0, 1)};
    tuple_t color = color_at(&world, &ray);
    munit_assert(tuple_cmp2(color, vector(0.38066, 0.47583, 0.2855)));

    return MUNIT_OK;
}

TEST(test_color_intersection_behind_ray) {
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
    material.ambient = 1.0;
    s1.material = material;

    object_t s2;
    sphere_init(&s2);
    s2.type_name = SPHERE;
    s2.material = material;
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    ray_t ray = {point(0, 0, 0.75), vector(0, 0, -1)};
    tuple_t color = color_at(&world, &ray);

    munit_assert(tuple_cmp2(color, s2.material.color));

    return MUNIT_OK;
}

TEST(test_no_shadow_when_nothing_collinear) {
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

    tuple_t p = point(0, 10, 0);

    munit_assert_false(is_shadowed(&world, p));

    return MUNIT_OK;
}

TEST(test_shadow_when_object_between) {
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

    tuple_t p = point(10, -10, 10);

    munit_assert(is_shadowed(&world, p));

    return MUNIT_OK;
}

TEST(test_no_shadow_when_object_behind_light) {
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

    tuple_t p = point(-20, 20, -20);

    munit_assert_false(is_shadowed(&world, p));

    return MUNIT_OK;
}

TEST(test_no_shadow_when_object_behind_point) {
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

    tuple_t p = point(-2, 2, -2);

    munit_assert_false(is_shadowed(&world, p));

    return MUNIT_OK;
}

#define WORLD_TESTS \
    {             \
        "intersect a world with a ray", \
        test_world_intersection, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {             \
        "hit when an intersection occurs on the outside", \
        test_hit_occur_outside, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {             \
        "hit when an intersection occurs on the inside", \
        test_hit_occur_inside, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {             \
        "shading an intersection", \
        test_shade_intersectoin, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {             \
        "shading an intersection from the inside", \
        test_shade_intersectoin_inside, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "the color when a ray misses", \
        test_color_ray_misses, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "the color when a ray hits", \
        test_color_ray_hits, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "the color with an intersection behind the ray", \
        test_color_intersection_behind_ray, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "no shadow when nothing is collinear with point and light", \
        test_no_shadow_when_nothing_collinear, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "The shadow when and object is between the point and the light", \
        test_shadow_when_object_between, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "The shadow when an object is behind the light", \
        test_no_shadow_when_object_behind_light, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "Theres is no shadow when an object is behind the light", \
        test_no_shadow_when_object_behind_point, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }


#endif //RAY_TRACER_IN_C_WORLD_TEST_H
