//
// Created by ryousuke kaga on 2023/10/31.
//

#ifndef RAY_TRACER_IN_C_TRANSFORMATION_H
#define RAY_TRACER_IN_C_TRANSFORMATION_H

#include "tuple.h"
#include "matrix.h"

matrix_t* view_transform(tuple_t from, tuple_t to, tuple_t up, matrix_t* buf);

#endif //RAY_TRACER_IN_C_TRANSFORMATION_H
