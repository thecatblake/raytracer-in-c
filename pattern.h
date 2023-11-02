//
// Created by ryousuke kaga on 2023/11/02.
//

#ifndef RAY_TRACER_IN_C_PATTERN_H
#define RAY_TRACER_IN_C_PATTERN_H

#include "tuple.h"
#include "matrix.h"

enum pattern {
    NO_PATTERN,
    STRIPE
};

typedef struct pattern_s {
    enum pattern type;
    void* obj;
    matrix_t transform;
} pattern_t;

typedef struct stripe_pattern_s {
    tuple_t a;
    tuple_t b;
} stripe_pattern_t;

void pattern_init(pattern_t* pattern);
void stripe_init(pattern_t* pattern, stripe_pattern_t* stripe);
tuple_t stripe_at(pattern_t* stripe, tuple_t position);

#endif //RAY_TRACER_IN_C_PATTERN_H
