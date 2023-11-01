//
// Created by ryousuke kaga on 2023/11/02.
//

#include "plane.h"

void plane_init(object_t* object) {
    object_init(object);
    object->type_name = PLANE;
}

tuple_t plane_normal_at(object_t* plane, tuple_t point) {
    matrix_t m;
    return tuple_transform(*matrix_inv(plane->origin_transform, &m), point(0, 1, 0));
}

void plane_hit(ray_t* ray, double* buf, int* hit_num) {
    if (fabs(ray->direction.y) < EPSILON_DEFAULT) {
        *hit_num = 0;
        return;
    }

    double t = -ray->origin.y / ray->direction.y;
    *hit_num = 1;
    buf[0] = t;
}