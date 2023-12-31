cmake_minimum_required(VERSION 3.25)
project(ray_tracer_in_C C)

set(CMAKE_C_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(munit munit/munit.c)
add_library(algorithms algorithms/list.c algorithms/heap.c)
add_library(raytracer
        util.c
        tuple.c
        matrix.c
        ray.c
        object.c
        sphere.c
        canvas.c
        material.c
        light.c
        world.c
        transformation.c
        camera.c
        plane.c
        pattern.c
        pattern.h
        cube.c
        cube.h
        cylinder.c
        cylinder.h
        intersection.h
        group.c
        group.h
)

add_executable(ray_tracer_in_C main.c)
add_executable(test test/tests.c
        test/light_test.h
        test/world_test.h
        test/transformation_test.h
        test/camera_test.h
        test/plane_test.h
        test/pattern_test.h
        test/cube_test.h
        test/cylinder_test.h
        test/group_test.h)
add_executable(sphere_image sphere_image.c)
add_executable(plane_sphere_image plane_sphere_image.c)
add_executable(glass_plane_sphere glass_plane_sphere.c)
add_executable(cube_image cube_image.c)
add_executable(cylinder_image cylinder_image.c)
add_executable(hexagon_image hexagon_image.c)
target_link_libraries(raytracer algorithms)
target_link_libraries(ray_tracer_in_C raytracer)
target_link_libraries(test munit raytracer)
target_link_libraries(sphere_image raytracer)
target_link_libraries(plane_sphere_image raytracer)
target_link_libraries(glass_plane_sphere raytracer)
target_link_libraries(cube_image raytracer)
target_link_libraries(cylinder_image raytracer)
target_link_libraries(hexagon_image raytracer)