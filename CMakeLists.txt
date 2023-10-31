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
)

add_executable(ray_tracer_in_C main.c)
add_executable(test test/tests.c
        test/light_test.h
        test/world_test.h
        test/transformation_test.h
        test/camera_test.h)
add_executable(sphere_image sphere_image.c)
target_link_libraries(raytracer algorithms)
target_link_libraries(ray_tracer_in_C raytracer)
target_link_libraries(test munit raytracer)
target_link_libraries(sphere_image raytracer)
