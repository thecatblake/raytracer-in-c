//
// Created by ryousuke kaga on 2023/10/26.
//

#include "object.h"

void object_init(object_t* object) {
    matrix_id(&object->transform);
}
void add_transform(object_t* object, matrix_t transform) {
    matrix_mul(transform, object->transform, &object->transform);
}