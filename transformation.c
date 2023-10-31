//
// Created by ryousuke kaga on 2023/10/31.
//

#include "transformation.h"

matrix_t* view_transform(tuple_t from, tuple_t to, tuple_t up, matrix_t* buf) {
    tuple_t forward = tuple_norm(tuple_sub(to, from));
    tuple_t left = tuple_cross(forward, tuple_norm(up));
    tuple_t true_up = tuple_cross(left, forward);

    matrix_t orientation = {left.x, left.y, left.z, 0,
                       true_up.x, true_up.y, true_up.z, 0,
                       -forward.x, -forward.y, -forward.z, 0,
                       0, 0, 0, 1};

    matrix_t t;
    matrix_mul(orientation, *translation_matrix(-from.x, -from.y, -from.z, &t), buf);

    return buf;
}