//
// Created by ryousuke kaga on 2023/10/26.
//

#ifndef RAY_TRACER_IN_C_OBJECT_H
#define RAY_TRACER_IN_C_OBJECT_H

#include "matrix.h"

typedef struct object_s {
    matrix_t transform;
} object_t;

void object_init(object_t* object);
void add_transform(object_t* object, matrix_t transform);

#endif //RAY_TRACER_IN_C_OBJECT_H
