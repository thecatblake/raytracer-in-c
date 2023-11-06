//
// Created by ryousuke kaga on 2023/11/04.
//

#ifndef RAY_TRACER_IN_C_CUBE_H
#define RAY_TRACER_IN_C_CUBE_H

#include "tuple.h"
#include "ray.h"
#include "object.h"
#include "intersection.h"

void cube_hit(object_t* cube, ray_t* ray, intersection_t* buf, int* hit_num);
void cube_init(object_t* object);
tuple_t cube_normal_at(object_t* cube, tuple_t point);

#endif //RAY_TRACER_IN_C_CUBE_H
