//
// Created by ryousuke kaga on 2023/10/26.
//

#ifndef RAY_TRACER_IN_C_OBJECT_H
#define RAY_TRACER_IN_C_OBJECT_H

#include "matrix.h"
#include "material.h"

typedef struct object_s {
    matrix_t origin_transform;
    matrix_t direction_transform;
    material_t material;
} object_t;

void object_init(object_t* object);
void add_transform(object_t* object, matrix_t transform);
void object_translate(object_t* object, tuple_t translation);
void object_scale(object_t* object, tuple_t scale);
void object_rotate(object_t* object, tuple_t rotation);

#endif //RAY_TRACER_IN_C_OBJECT_H
