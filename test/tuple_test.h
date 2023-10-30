//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_TUPLE_TEST_H
#define RAYTRACING_IN_C_TUPLE_TEST_H

#include "tests.h"

TEST(test_tuple_instantiation) {
    tuple_t a = {4.3f, -4.2f, 3.1f, 1};
    munit_assert(a.x == 4.3f);
    munit_assert(a.y == -4.2f);
    munit_assert(a.z == 3.1f);
    munit_assert(a.w == 1);

    return MUNIT_OK;
}

TEST(test_tuple_comparison) {
    tuple_t a1 = {3, -2, 5, 1};
    tuple_t a2 = {-2, 3, 1, 0};
    tuple_t a3 = {3, -2, 5, 1};
    munit_assert(tuple_cmp2(a1, a2) == 0);
    munit_assert(tuple_cmp2(a1, a3) == 1);

    return MUNIT_OK;
}

TEST(test_point_creation) {
    tuple_t p = point(4.0f, -4.0f, 3.0f);
    tuple_t t = {4.0f, -4.0f, 3.0f, 1};
    munit_assert(tuple_cmp2(p, t));

    return MUNIT_OK;
}

TEST(test_vector_creation) {
    tuple_t v = vector(4.0f, -4.0f, 3.0f);
    tuple_t t = {4.0f, -4.0f, 3.0f, 0};
    munit_assert(tuple_cmp2(v, t));

    return MUNIT_OK;
}

TEST(test_tuple_addition) {
    tuple_t a1 = {3, -2, 5, 1};
    tuple_t a2 = {-2, 3, 1, 0};
    tuple_t a3 = tuple_add(a1, a2);
    tuple_t t = {1.0f, 1.0f, 6.0f, 1};
    munit_assert(tuple_cmp2(a3, t));

    return MUNIT_OK;
}

TEST(test_tuple_subtraction) {
    tuple_t a1 = {3, 2, 1, 1};
    tuple_t a2 = {5, 6, 7, 1};
    tuple_t a3 = tuple_sub(a1, a2);
    tuple_t t = {-2.0f, -4.0f, -6.0f, 0};
    munit_assert(tuple_cmp2(a3, t));

    return MUNIT_OK;
}

TEST(test_tuple_negation) {
    tuple_t a1 = {3, 2, 1, 1};
    tuple_t a2 = tuple_neg(a1);
    tuple_t t = {-3.0f, -2.0f, -1.0f, -1};
    munit_assert(tuple_cmp2(a2, t));

    return MUNIT_OK;
}

TEST(test_tuple_scalar_multiplication) {
    tuple_t a1 = {1, -2, 3, -4};
    tuple_t a2 = tuple_sc_mul(a1, 3.5f);
    tuple_t t = {3.5f, -7.0f, 10.5f, -14};
    munit_assert(tuple_cmp2(a2, t));

    return MUNIT_OK;
}

TEST(test_tuple_scalar_division) {
    tuple_t a1 = {1, -2, 3, -4};
    tuple_t a2 = tuple_sc_div(a1, 2);
    tuple_t t = {0.5f, -1.0f, 1.5f, -2};
    munit_assert(tuple_cmp2(a2, t));

    return MUNIT_OK;
}

TEST(test_tuple_magnitude) {
    tuple_t v = vector(-1, -2, -3);
    munit_assert(double_cmp(sqrt(14), tuple_mag(v), EPSILON_DEFAULT));

    return MUNIT_OK;
}

TEST(test_tuple_normalization) {
    tuple_t v = vector(1, 2, 3);
    double mag = tuple_mag(v);
    tuple_t t = vector(1/mag, 2/mag, 3/mag);
    munit_assert(tuple_cmp2(tuple_norm(v), t));

    return MUNIT_OK;
}

TEST(test_tuple_dot_product) {
    tuple_t a1 = vector(1, 2, 3);
    tuple_t a2 = vector(2, 3, 4);
    munit_assert(double_cmp2(tuple_dot(a1, a2), 20));

    return MUNIT_OK;
}

TEST(test_tuple_cross_product) {
    tuple_t a1 = vector(1, 2, 3);
    tuple_t a2 = vector(2, 3, 4);
    tuple_t t1 = vector(-1, 2, -1);
    tuple_t t2 = vector(1, -2, 1);
    munit_assert(tuple_cmp2(tuple_cross(a1, a2), t1));
    munit_assert(tuple_cmp2(tuple_cross(a2, a1), t2));

    return MUNIT_OK;
}

TEST(test_tuple_multiplication) {
    tuple_t a1 = vector(1, 0.2, 0.4);
    tuple_t a2 = vector(0.9, 1, 0.1);
    tuple_t t = vector(0.9, 0.2, 0.04);
    munit_assert(tuple_cmp2(tuple_mul(a1, a2), t));

    return MUNIT_OK;
}

TEST(test_tuple_reflection) {
    tuple_t v = vector(0, -1, 0);
    tuple_t n = vector(sqrt(2)/2, sqrt(2)/2, 0);
    munit_assert(tuple_cmp2(vector(1, 0, 0), tuple_reflect(v, n)));

    return MUNIT_OK;
}

#define TUPLE_TESTS \
    {               \
        "tuple_instantiation", \
        test_tuple_instantiation, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    },              \
    {               \
        "tuple_comparison", \
        test_tuple_comparison, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    },                 \
    {               \
        "point_creation",      \
        test_point_creation,   \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    }, \
    {               \
        "vector_creation",      \
        test_vector_creation,   \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    }, \
    {               \
        "tuple_addition",      \
        test_tuple_addition,   \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    },              \
    {               \
        "tuple_subtraction",      \
        test_tuple_subtraction,   \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    },              \
    {               \
        "tuple_multiplication",      \
        test_tuple_multiplication,   \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    },                \
    {               \
        "tuple_negation",      \
        test_tuple_negation,   \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    },              \
    {               \
        "tuple_scalar_multiplication",      \
        test_tuple_scalar_multiplication,   \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    },              \
    {               \
        "tuple_scalar_division",      \
        test_tuple_scalar_division,   \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    },              \
    {               \
        "tuple_magnitude",      \
        test_tuple_magnitude,   \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    },              \
    {               \
        "tuple_normalization",      \
        test_tuple_normalization,   \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    },              \
    {               \
        "tuple_dot_product",      \
        test_tuple_dot_product,   \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    },              \
    {               \
        "tuple_cross_product",      \
        test_tuple_cross_product,   \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    },              \
    {               \
        "tuple_reflection",      \
        test_tuple_reflection,   \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    }

#endif //RAYTRACING_IN_C_TUPLE_TEST_H
