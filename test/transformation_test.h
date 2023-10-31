//
// Created by ryousuke kaga on 2023/10/31.
//

#ifndef RAY_TRACER_IN_C_TRANSFORMATION_TEST_H
#define RAY_TRACER_IN_C_TRANSFORMATION_TEST_H

#include "tests.h"

TEST(test_transformation_matrix_default_orientation) {
    matrix_t t, id;
    view_transform(point(0, 0, 0), point(0, 0, -1), point(0, 1, 0), &t);
    matrix_id(&id);

    munit_assert(matrix_cmp2(t, id));

    return MUNIT_OK;
}

TEST(test_transformation_matrix_looking_positive_z) {
    matrix_t t, scale;
    view_transform(point(0, 0, 0), point(0, 0, 1), point(0, 1, 0), &t);
    scaling_matrix(-1, 1, -1, &scale);
    munit_assert(matrix_cmp2(t, scale));

    return MUNIT_OK;
}

TEST(test_view_transformation_moves) {
    matrix_t t, trans;
    view_transform(point(0, 0, 8), point(0, 0, 0), point(0, 1, 0), &t);
    translation_matrix(0, 0, -8, &trans);
    munit_assert(matrix_cmp2(t, trans));

    return MUNIT_OK;
}

TEST(test_arbitrary_view_transformation) {
    matrix_t t;
    view_transform(point(1, 3, 2), point(4, -2, 8), point(1, 1, 0), &t);

    matrix_t result = {-0.50709, 0.50709, 0.67612, -2.36643,
                       0.76772, 0.60609, 0.12122, -2.82843,
                       -0.35857, 0.59761, -0.71714, 0.00000,
                       0.00000, 0.00000, 0.00000, 1.00000};

    munit_assert(matrix_cmp2(t, result));

    return MUNIT_OK;
}

#define TRANSFORMATION_TESTS \
    {             \
        "The transformation matrix for the default orientation", \
        test_transformation_matrix_default_orientation, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },            \
    {             \
        "A view transformation matrix looking in positive z direction", \
        test_transformation_matrix_looking_positive_z, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },            \
    {             \
        "The view transformation moves the world", \
        test_view_transformation_moves, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },            \
    {             \
        "An arbitrary view transformation", \
        test_arbitrary_view_transformation, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }


#endif //RAY_TRACER_IN_C_TRANSFORMATION_TEST_H
