//
// Created by ryousuke kaga on 2023/10/26.
//

#ifndef RAY_TRACER_IN_C_OBJECT_H
#define RAY_TRACER_IN_C_OBJECT_H

#include "matrix.h"
#include "material.h"
#include "transformation.h"

enum object_type_name {
    EMPTY_OBJECT,
    SPHERE,
    PLANE,
    CUBE,
    CYLINDER
};

typedef struct object_s {
    enum object_type_name type_name;
    matrix_t origin_transform;
    matrix_t direction_transform;
    material_t material;
} object_t;

void object_init(object_t* object);
void object_translate(object_t* object, tuple_t translation);
void object_scale(object_t* object, tuple_t scale);
void object_rotate_x(object_t* object, double rad);
void object_rotate_y(object_t* object, double rad);
void object_rotate_z(object_t* object, double rad);

#endif //RAY_TRACER_IN_C_OBJECT_H
