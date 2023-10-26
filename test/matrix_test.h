//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_MATRIX_TEST_H
#define RAYTRACING_IN_C_MATRIX_TEST_H

#include "tests.h"

TEST(test_matrix_zero) {
    matrix_t m;
    matrix_zero(&m);
    for(int i=0; i < 16; i++) {
        munit_assert(m[i] == 0);
    }

    return MUNIT_OK;
}

TEST(test_matrix_set) {
    matrix_t m;
    matrix_set(m, 1, 2, 5.0);
    munit_assert(m[2*4+1] == 5.0);

    return MUNIT_OK;
}

TEST(test_matrix_comparison) {
    matrix_t a;
    matrix_t b;
    matrix_zero(&a);
    matrix_zero(&b);

    munit_assert(matrix_cmp2(a, b));

    return MUNIT_OK;
}

TEST(test_matrix_multiplication) {
    matrix_t a = {1, 2, 1, 2,
                  1, 2, 1, 2,
                  1, 2, 1, 2,
                  1, 2, 1, 2};
    matrix_t b = {0, 1, 0, 1,
                  0, 1, 0, 1,
                  0, 1, 0, 1,
                  0, 1, 0, 1};
    matrix_t t1 = {0, 6, 0, 6,
                  0, 6, 0, 6,
                  0, 6, 0, 6,
                  0, 6, 0, 6};
    matrix_t t2 = {2, 4, 2, 4,
                   2, 4, 2, 4,
                   2, 4, 2, 4,
                   2, 4, 2, 4};
    matrix_t tmp;

    munit_assert(matrix_cmp2(*matrix_mul(a, b, &tmp), t1));
    munit_assert(matrix_cmp2(*matrix_mul(b, a, &tmp), t2));

    return MUNIT_OK;
}

TEST(test_matrix_identity) {
    matrix_t m = {1, 2, 1, 2,
                  1, 2, 1, 2,
                  1, 2, 1, 2,
                  1, 2, 1, 2};
    matrix_t id;
    matrix_t tmp;

    munit_assert(matrix_cmp2(*matrix_mul(*matrix_id(&id), m, &tmp), m));

    return MUNIT_OK;
}

TEST(test_matrix_transpose) {
    matrix_t m = {1, 2, 1, 2,
                  1, 2, 1, 2,
                  1, 2, 1, 2,
                  1, 2, 1, 2};
    matrix_t t = {1, 1, 1, 1,
                  2, 2, 2, 2,
                  1, 1, 1, 1,
                  2, 2, 2, 2};
    matrix_t tmp;

    munit_assert(matrix_cmp2(*matrix_T(m, &tmp), t));

    return MUNIT_OK;
}

TEST(test_matrix_determinant) {
    matrix_t m = {1, 2, 3, 4,
                  5, 6, 7, 8,
                  9, 2, 3, 5,
                  4, 3, 6, 8};

    munit_assert(double_cmp2(matrix_det(m), 48));

    return MUNIT_OK;
}

TEST(test_matrix_invertible) {
    matrix_t a = {1, 2, 3, 4,
                  5, 6, 7, 8,
                  9, 2, 3, 4,
                  4, 3, 6, 8};
    matrix_t b = {1, 2, 3, 4,
                  5, 6, 7, 8,
                  9, 1, 2, 3,
                  4, 5, 6, 7};

    munit_assert(matrix_is_invertible(a));
    munit_assert_false(matrix_is_invertible(b));

    return MUNIT_OK;
}

TEST(test_matrix_inversion) {
    matrix_t a = {1, 2, 3, 4,
                  5, 6, 7, 8,
                  9, 2, 3, 4,
                  4, 3, 6, 8};
    matrix_t id;
    matrix_id(&id);

    matrix_t tmp1;
    matrix_t tmp2;

    munit_assert(matrix_cmp2(*matrix_mul(*matrix_inv(a, &tmp1), a, &tmp2), id));

    return MUNIT_OK;
}


TEST(test_matrix_translation) {
    matrix_t t;
    tuple_t p = point(1, 0, 0);

    munit_assert(tuple_cmp2(tuple_transform(*translation_matrix(1, 1, 1, &t), p), point(2, 1, 1)));
}

TEST(test_matrix_scaling) {
    matrix_t t;
    tuple_t p = point(1, 0, 0);

    munit_assert(tuple_cmp2(tuple_transform(*scaling_matrix(2, 2, 2, &t), p), point(2, 0, 0)));
}

TEST(test_matrix_rotation_x) {
    matrix_t t;
    tuple_t p = point(1, 1, 1);

    munit_assert(tuple_cmp2(tuple_transform(*rotation_x_matrix(M_PI/2, &t), p), point(1, -1, 1)));
}

TEST(test_matrix_rotation_y) {
    matrix_t t;
    tuple_t p = point(1, 1, 1);

    munit_assert(tuple_cmp2(tuple_transform(*rotation_y_matrix(M_PI/2, &t), p), point(1, 1, -1)));
}

TEST(test_matrix_rotation_z) {
    matrix_t t;
    tuple_t p = point(1, 1, 1);

    munit_assert(tuple_cmp2(tuple_transform(*rotation_z_matrix(M_PI/2, &t), p), point(-1, 1, 1)));
}

#define MATRIX_TESTS \
    {                \
        "matrix_zerp", \
        test_matrix_zero, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_set", \
        test_matrix_set, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_comparison", \
        test_matrix_comparison, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_multiplication", \
        test_matrix_multiplication, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_identity", \
        test_matrix_identity, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_transpose", \
        test_matrix_transpose, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },           \
    {                \
        "matrix_determinant", \
        test_matrix_determinant, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_invertible", \
        test_matrix_invertible, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_inversion", \
        test_matrix_inversion, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_translation", \
        test_matrix_translation, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_scaling", \
        test_matrix_scaling, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_rotation_x", \
        test_matrix_rotation_x, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
        {                \
        "matrix_rotation_y", \
        test_matrix_rotation_y, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_rotation_z", \
        test_matrix_rotation_z, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    }



#endif //RAYTRACING_IN_C_MATRIX_TEST_H

