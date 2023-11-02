//
// Created by ryousuke kaga on 2023/10/31.
//

#ifndef RAY_TRACER_IN_C_TRANSFORMATION_H
#define RAY_TRACER_IN_C_TRANSFORMATION_H

#include "tuple.h"
#include "matrix.h"

typedef matrix_t transformation_t;

transformation_t* view_transform(tuple_t from, tuple_t to, tuple_t up, transformation_t* buf);
void transform_translate(matrix_t* to, tuple_t translate);
void transform_scale(matrix_t* to, tuple_t scale);
void transform_rotate_x(matrix_t* to, double rad);
void transform_rotate_y(matrix_t* to, double rad);
void transform_rotate_z(matrix_t* to, double rad);

#define add_transform(to, transform, buf) matrix_mul((to), (transform), (buf))

#endif //RAY_TRACER_IN_C_TRANSFORMATION_H
