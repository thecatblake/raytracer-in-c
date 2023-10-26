//
// Created by ryousuke kaga on 2023/10/05.
//

#include "ray.h"

tuple_t ray_position(ray_t* r, double t) {
    tuple_t result = tuple_add(r->origin, tuple_sc_mul(r->direction, t));
    result.w = 1;

    return result;
}

void ray_cpy(ray_t* destination, ray_t* source) {
    tuple_cpy(&destination->origin, &source->origin);
    tuple_cpy(&destination->direction, &source->direction);
}
