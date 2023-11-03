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

    computation_t computation = prepare_computation(intersection, &ray, NULL);

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

    computation_t computation = prepare_computation(intersection, &ray, NULL);

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
    
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    ray_t ray = {point(0, 0, -5), vector(0, 0, 1)};
    Heap intersections = world_intersect(&world, &ray);
    intersection_t* intersection;
    heap_extract(&intersections, (void**)&intersection);
    computation_t computation = prepare_computation(intersection, &ray, NULL);
    tuple_t color = shade_hit(&world, &computation, 1);
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
    
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    ray_t ray = {point(0, 0, 0 ), vector(0, 0, 1)};
    Heap intersections = world_intersect(&world, &ray);

    munit_assert(intersections.size == 2);

    intersection_t* intersection;
    heap_extract(&intersections, (void**)&intersection);
    munit_assert(double_cmp2(intersection->t, 0.5));

    computation_t computation = prepare_computation(intersection, &ray, NULL);
    tuple_t color = shade_hit(&world, &computation, 1);
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
    
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    ray_t ray = {point(0, 0, -5), vector(0, 1, 0)};
    tuple_t color = color_at(&world, &ray, 1);
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
    
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    ray_t ray = {point(0, 0, -5), vector(0, 0, 1)};
    tuple_t color = color_at(&world, &ray, 1);
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
    
    s2.material = material;
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    ray_t ray = {point(0, 0, 0.75), vector(0, 0, -1)};
    tuple_t color = color_at(&world, &ray, 1);

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
    
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    tuple_t p = point(-2, 2, -2);

    munit_assert_false(is_shadowed(&world, p));

    return MUNIT_OK;
}

TEST(test_precompute_reflection_vector) {
    object_t plane;
    plane_init(&plane);
    ray_t ray = {point(0, 1, -1), vector(0, -sqrt(2)/2, sqrt(2)/2)};
    intersection_t intersection = {sqrt(2), &plane};
    computation_t computation = prepare_computation(&intersection, &ray, NULL);
    munit_assert(tuple_cmp2(computation.reflectv, vector(0, sqrt(2)/2, sqrt(2)/2)));

    return MUNIT_OK;
}

TEST(test_reflected_color_for_nonreflective_material) {
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
    
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    ray_t ray = {point(0, 0, 0), vector(0, 0, 1)};
    s2.material.ambient = 1;
    intersection_t intersection = {1, &s2};
    computation_t computation = prepare_computation(&intersection, &ray, NULL);
    tuple_t color = reflected_color(&world, &computation, 1);

    munit_assert(tuple_cmp2(color, vector(0, 0, 0)));

    return MUNIT_OK;
};

TEST(test_reflexted_color_for_reflective_material) {
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
    
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    object_t shape;
    plane_init(&shape);
    shape.material.reflective = 0.5;
    object_translate(&shape, vector(0, -1, 0));
    world_add_object(&world, &shape);

    ray_t ray = {point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2)};
    intersection_t intersection = {sqrt(2), &shape};
    computation_t computation = prepare_computation(&intersection, &ray, NULL);
    tuple_t color = reflected_color(&world, &computation, 1);

    munit_assert(tuple_cmp2(color, vector(0.19032, 0.2379, 0.14272)));

    return MUNIT_OK;
};

TEST(test_shade_hit_with_reflective_material) {
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
    
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    object_t shape;
    plane_init(&shape);
    shape.material.reflective = 0.5;
    object_translate(&shape, vector(0, -1, 0));
    world_add_object(&world, &shape);

    ray_t ray = {point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2)};
    intersection_t intersection = {sqrt(2), &shape};
    computation_t computation = prepare_computation(&intersection, &ray, NULL);

    tuple_t color = shade_hit(&world, &computation, 1);

    munit_assert(tuple_cmp2(color, vector(0.87677, 0.92436, 0.82918)));

    return MUNIT_OK;
}

TEST(test_color_at_with_mutually_reflective_surface) {
    world_t world;
    world_init(&world);
    point_light_t light = {point(0, 0, 0), vector(1, 1, 1)};
    world.light = &light;
    object_t lower;
    plane_init(&lower);
    lower.material.reflective = 1;
    object_translate(&lower, vector(0, 1, 0));
    object_t upper;
    plane_init(&upper);
    upper.material.reflective = 1;
    object_translate(&upper, vector(0, 1, 0));
    world_add_object(&world, &lower);
    world_add_object(&world, &upper);

    ray_t ray = {point(0, 0, 0), vector(0, 1, 0)};

    tuple_t color = color_at(&world, &ray, 1);

    return MUNIT_OK;
};

TEST(test_reflected_color_at_maximum_recursive_depth) {
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
    
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    object_t shape;
    plane_init(&shape);
    shape.material.reflective = 0.5;
    object_translate(&shape, vector(0, -1, 0));

    ray_t ray = {point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2)};
    intersection_t intersection = {sqrt(2), &shape};
    computation_t computation = prepare_computation(&intersection, &ray, NULL);
    tuple_t color = reflected_color(&world, &computation, 0);

    munit_assert(tuple_cmp2(color, vector(0, 0, 0)));

    return MUNIT_OK;
};

TEST(test_finding_n1_n2_at_intersections) {
    object_t A;
    glass_sphere_init(&A);
    object_scale(&A, vector(2, 2, 2));
    A.material.refractive_index = 1.5;
    object_t B;
    glass_sphere_init(&B);
    object_translate(&B, vector(0, 0, -0.25));
    B.material.refractive_index = 2.0;
    object_t C;
    glass_sphere_init(&C);
    object_translate(&C, vector(0, 0, 0.25));
    C.material.refractive_index = 2.5;

    ray_t ray = {point(0, 0, -4), vector(0, 0, 1)};
    intersection_t xs[6] = {
            {2, &A},
            {2.75, &B},
            {3.25, &C},
            {4.75, &B},
            {5.25, &C},
            {6, &A}
    };

    double ts[6][2] = {
            {1.0, 1.5},
            {1.5, 2.0},
            {2.0, 2.5},
            {2.5, 2.5},
            {2.5, 1.5},
            {1.5, 1.0}
    };

    List intersections;
    list_init(&intersections, NULL);
    for(int i=0; i < 6; i++) {
        munit_assert(list_ins_next(&intersections, intersections.tail, &xs[i]) == 0);
    }

    for(int i=0; i < 6; i++) {
        computation_t computation = prepare_computation(&xs[i], &ray, &intersections);

        munit_assert(double_cmp2(computation.n1, ts[i][0]));
        munit_assert(double_cmp2(computation.n2, ts[i][1]));
    }

    list_destroy(&intersections);

    return MUNIT_OK;
};

TEST(test_refracted_color_with_opaque_surface) {
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
    
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    ray_t ray = {point(0, 0, -5), vector(0, 0, 1)};
    intersection_t xs[] = {
            {4, &s1},
            {6, &s1},
    };
    List intersections;
    list_init(&intersections, NULL);
    list_ins_next(&intersections, intersections.tail, &xs[0]);
    list_ins_next(&intersections, intersections.tail, &xs[1]);
    computation_t computation = prepare_computation(&xs[0], &ray, &intersections);
    tuple_t color = refracted_color(&world, &computation, 5);

    munit_assert(tuple_cmp2(color, vector(0, 0, 0)));

    return MUNIT_OK;
};

TEST(test_refracted_color_at_maximum_recursive_depth) {
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
    material.transparency = 1.0;
    material.refractive_index = 1.5;
    s1.material = material;

    object_t s2;
    sphere_init(&s2);
    
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    ray_t ray = {point(0, 0, -5), vector(0, 0, 1)};
    intersection_t xs[] = {
            {4, &s1},
            {6, &s1},
    };
    List intersections;
    list_init(&intersections, NULL);
    list_ins_next(&intersections, intersections.tail, &xs[0]);
    list_ins_next(&intersections, intersections.tail, &xs[1]);
    computation_t computation = prepare_computation(&xs[0], &ray, &intersections);
    tuple_t color = refracted_color(&world, &computation, 0);

    munit_assert(tuple_cmp2(color, vector(0, 0, 0)));

    return MUNIT_OK;
};

TEST(test_refracetd_color_under_total_internal_reflection) {
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
    material.transparency = 1.0;
    material.refractive_index = 1.5;
    s1.material = material;

    object_t s2;
    sphere_init(&s2);
    
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    ray_t ray = {point(0, 0, sqrt(2)/2), vector(0, 1, 0)};
    intersection_t xs[] = {
            {-sqrt(2)/2, &s1},
            {sqrt(2)/2, &s1},
    };
    List intersections;
    list_init(&intersections, NULL);
    list_ins_next(&intersections, intersections.tail, &xs[0]);
    list_ins_next(&intersections, intersections.tail, &xs[1]);
    computation_t computation = prepare_computation(&xs[1], &ray, &intersections);
    tuple_t color = refracted_color(&world, &computation, 5);

    munit_assert(tuple_cmp2(color, vector(0, 0, 0)));

    return MUNIT_OK;
};

TEST(test_refracted_color_with_refracted_ray) {
    world_t world;
    world_init(&world);

    point_light_t light = {point(-10, 10, -10), vector(1, 1, 1)};
    world.light = &light;
    
    pattern_t pattern;
    testpattern_init(&pattern);

    object_t s1;
    sphere_init(&s1);
    s1.type_name = SPHERE;
    material_t material;
    material_init(&material);
    material.color = vector(0.8, 1.0, 0.6);
    material.diffuse = 0.7;
    material.specular = 0.2;
    material.ambient = 1;
    material.pattern = pattern;
    s1.material = material;

    object_t s2;
    sphere_init(&s2);
    s2.material.transparency = 1.0;
    s2.material.refractive_index = 1.5;
    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    ray_t ray = {point(0, 0, 0.1), vector(0, 1, 0)};
    intersection_t xs[] = {
            {-0.9899, &s1},
            {-0.4899, &s2},
            {0.4899, &s2},
            {0.9899, &s1}
    };
    List intersections;
    list_init(&intersections, NULL);
    list_ins_next(&intersections, intersections.tail, &xs[0]);
    list_ins_next(&intersections, intersections.tail, &xs[1]);
    list_ins_next(&intersections, intersections.tail, &xs[2]);
    list_ins_next(&intersections, intersections.tail, &xs[3]);
    computation_t computation = prepare_computation(&xs[2], &ray, &intersections);
    tuple_t color = refracted_color(&world, &computation, 5);
    munit_assert(tuple_cmp2(color, vector(0, 0.99888, 0.04725)));

    return MUNIT_OK;
}

TEST(test_shade_hit_with_transparent_material) {
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

    object_scale(&s2, vector(0.5, 0.5, 0.5));

    world_add_object(&world, &s1);
    world_add_object(&world, &s2);

    object_t floor;
    plane_init(&floor);
    object_translate(&floor, vector(0, -1, 0));
    floor.material.transparency = 0.5;
    floor.material.refractive_index = 1.5;

    object_t ball;
    sphere_init(&ball);
    object_translate(&ball, vector(0, -3.5, -0.5));
    ball.material.color = vector(1, 0, 0);
    ball.material.ambient = 0.5;

    world_add_object(&world, &floor);
    world_add_object(&world, &ball);

    ray_t ray = {point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2)};
    intersection_t xs[] = {
            {sqrt(2), &floor}
    };
    List intersections;
    list_init(&intersections, NULL);
    list_ins_next(&intersections, intersections.tail, &xs[0]);

    computation_t computation = prepare_computation(&xs[0], &ray, &intersections);
    tuple_t color = shade_hit(&world, &computation, 5);

    munit_assert(tuple_cmp2(color, vector(0.93642, 0.68642, 0.68642)));

    return MUNIT_OK;
};

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
    },              \
    {                \
        "Precomputing the reflection vector", \
        test_precompute_reflection_vector, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "The reflected color for a non-reflective material", \
        test_reflected_color_for_nonreflective_material, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "The reflected color for a reflective material", \
        test_reflexted_color_for_reflective_material, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "shade_hit with a reflective material", \
        test_shade_hit_with_reflective_material, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "color_at with mutually reflective surfaces", \
        test_color_at_with_mutually_reflective_surface, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "The reflected color at the maximum recursive depth", \
        test_reflected_color_at_maximum_recursive_depth, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "Finding n1 and n2 at various intersections", \
        test_finding_n1_n2_at_intersections, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "The refracted color with an opaque surface", \
        test_refracted_color_with_opaque_surface, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "The refracted color at the maximum recursive depth", \
        test_refracted_color_at_maximum_recursive_depth, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "The refracted color under total internal reflection", \
        test_refracetd_color_under_total_internal_reflection, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "the refracted color with a refracted ray", \
        test_refracted_color_with_refracted_ray, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {                \
        "shade_hit with a transparent material", \
        test_shade_hit_with_transparent_material, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }


#endif //RAY_TRACER_IN_C_WORLD_TEST_H
