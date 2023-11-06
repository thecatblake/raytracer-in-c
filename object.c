//
// Created by ryousuke kaga on 2023/10/26.
//

#include "object.h"

void object_init(object_t* object) {
    object->type_name = EMPTY_OBJECT;
    matrix_id(&object->origin_transform);
    matrix_id(&object->direction_transform);
    material_init(&object->material);
    object->data = NULL;
    object->parent = NULL;
}

void object_translate(object_t* object, tuple_t translation) {
    matrix_t t;
    translation_matrix(translation.x, translation.y, translation.z, &t);
    add_transform(t, object->origin_transform, &object->origin_transform);
}

void object_scale(object_t* object, tuple_t scale) {
    matrix_t t;
    scaling_matrix(scale.x, scale.y, scale.z, &t);
    add_transform(t, object->origin_transform, &object->origin_transform);
    add_transform(t, object->direction_transform, &object->direction_transform);
}

void object_rotate_x(object_t* object, double rad) {
    matrix_t t;
    rotation_x_matrix(rad, &t);
    add_transform(t, object->origin_transform, &object->origin_transform);
    add_transform(t, object->direction_transform, &object->direction_transform);
}

void object_rotate_y(object_t* object, double rad) {
    matrix_t t;
    rotation_y_matrix(rad, &t);
    add_transform(t, object->origin_transform, &object->origin_transform);
    add_transform(t, object->direction_transform, &object->direction_transform);
}

void object_rotate_z(object_t* object, double rad) {
    matrix_t t;
    rotation_z_matrix(rad, &t);
    add_transform(t, object->origin_transform, &object->origin_transform);
    add_transform(t, object->direction_transform, &object->direction_transform);
}