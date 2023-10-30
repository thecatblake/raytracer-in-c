//
// Created by ryousuke kaga on 2023/10/26.
//

#include "object.h"

void object_init(object_t* object) {
    matrix_id(&object->origin_transform);
    matrix_id(&object->direction_transform);
    material_init(&object->material);
}

void object_translate(object_t* object, tuple_t translation) {
    matrix_t t;
    translation_matrix(translation.x, translation.y, translation.z, &t);
    matrix_mul(t, object->origin_transform, &object->origin_transform);
}

void object_scale(object_t* object, tuple_t scale) {
    matrix_t t;
    scaling_matrix(scale.x, scale.y, scale.z, &t);
    matrix_mul(t, object->origin_transform, &object->origin_transform);
    matrix_mul(t, object->direction_transform, &object->direction_transform);
}