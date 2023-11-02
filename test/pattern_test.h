//
// Created by ryousuke kaga on 2023/11/02.
//

#ifndef RAY_TRACER_IN_C_PATTERN_TEST_H
#define RAY_TRACER_IN_C_PATTERN_TEST_H

#include "tests.h"

TEST(test_stripe_patterns) {
    tuple_t white = vector(1, 1, 1);
    tuple_t black = vector(0, 0, 0);
    stripe_pattern_t stripe = {white, black};
    pattern_t pattern;
    stripe_init(&pattern, &stripe);

    munit_assert(tuple_cmp2(stripe_at(&pattern, point(0, 0, 0)), white));
    munit_assert(tuple_cmp2(stripe_at(&pattern, point(0, 1, 0)), white));
    munit_assert(tuple_cmp2(stripe_at(&pattern, point(0, 2, 0)), white));
    munit_assert(tuple_cmp2(stripe_at(&pattern, point(0, 0, 0)), white));
    munit_assert(tuple_cmp2(stripe_at(&pattern, point(0, 0, 1)), white));
    munit_assert(tuple_cmp2(stripe_at(&pattern, point(0, 0, 2)), white));
    munit_assert(tuple_cmp2(stripe_at(&pattern, point(0.9, 0, 0)), white));
    munit_assert(tuple_cmp2(stripe_at(&pattern, point(1, 0, 0)), black));
    munit_assert(tuple_cmp2(stripe_at(&pattern, point(-0.1, 0, 0)), black));

    return MUNIT_OK;
}


#define PATTERN_TESTS \
    {             \
        "test_stripe_patterns", \
        test_ray_instantiation, \
        NULL,     \
        NULL,     \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }


#endif //RAY_TRACER_IN_C_PATTERN_TEST_H
