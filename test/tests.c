//
// Created by ryousuke kaga on 2023/09/25.
//
#include "tests.h"
#include "tuple_test.h"
#include "matrix_test.h"
#include "ray_test.h"
#include "sphere_test.h"
#include "light_test.h"
#include "world_test.h"
#include "transformation_test.h"
#include "camera_test.h"
#include "plane_test.h"
#include "pattern_test.h"
#include "cube_test.h"
#include "cylinder_test.h"

MunitTest tests[] = {
        TUPLE_TESTS,
        MATRIX_TESTS,
        RAY_TESTS,
        SPHERE_TESTS,
        LIGHT_TESTS,
        WORLD_TESTS,
        TRANSFORMATION_TESTS,
        CAMERA_TESTS,
        PLANE_TESTS,
        PATTERN_TESTS,
        CUBE_TESTS,
        CYLINDER_TESTS
};

static const MunitSuite suite = {
        "/my-tests/", /* name */
        tests, /* tests */
        NULL, /* suites */
        1, /* iterations */
        MUNIT_SUITE_OPTION_NONE /* options */
};


int main (int argc, const char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}