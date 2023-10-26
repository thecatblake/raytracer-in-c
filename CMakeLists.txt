cmake_minimum_required(VERSION 3.25)
project(ray_tracer_in_C C)

set(CMAKE_C_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(munit munit/munit.c)
add_library(raytracer util.c tuple.c matrix.c ray.c object.c sphere.c canvas.c)

add_executable(ray_tracer_in_C main.c)
add_executable(test test/tests.c)
target_link_libraries(ray_tracer_in_C raytracer)
target_link_libraries(test munit raytracer)
