//
// Created by ryousuke kaga on 2023/11/02.
//

#include "pattern.h"

void pattern_init(pattern_t* pattern) {
    pattern->type = NO_PATTERN;
    pattern->obj = NULL;
    matrix_id(&pattern->transform);
}

void stripe_init(pattern_t* pattern, stripe_pattern_t* stripe) {
    pattern_init(pattern);
    pattern->type = STRIPE;
    pattern->obj = stripe;
}

void gradient_init(pattern_t* pattern, stripe_pattern_t* stripe) {
    pattern_init(pattern);
    pattern->type = GRADIENT;
    pattern->obj = stripe;
}

void check_init(pattern_t* pattern, stripe_pattern_t* stripe) {
    pattern_init(pattern);
    pattern->type = CHECK;
    pattern->obj = stripe;
}

tuple_t stripe_at(pattern_t* stripe_pattern, tuple_t position) {
    stripe_pattern_t* stripe = stripe_pattern->obj;

    if((int)floor(position.x) % 2 == 0)
        return stripe->a;

    return stripe->b;
}

tuple_t gradient_at(pattern_t* gradient, tuple_t position) {
    stripe_pattern_t* stripe = gradient->obj;
    tuple_t distance = tuple_sub(stripe->b, stripe->a);
    double fraction = position.x - floor(position.x);

    return tuple_add(stripe->a, tuple_sc_mul(distance, fraction));
}

tuple_t check_at(pattern_t* check, tuple_t position) {
    stripe_pattern_t* stripe = check->obj;

    if((int)(floor(position.x) + floor(position.y) + floor(position.z)) % 2 == 0)
        return stripe->a;

    return stripe->b;
}