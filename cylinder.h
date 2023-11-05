//
// Created by ryousuke kaga on 2023/11/05.
//

#ifndef RAY_TRACER_IN_C_CYLINDER_H
#define RAY_TRACER_IN_C_CYLINDER_H

#include "tuple.h"
#include "ray.h"
#include "object.h"

void cylinder_hit(ray_t* ray, double* buf, int* hit_num);
void cylinder_init(object_t* object);
tuple_t cylinder_normal_at(object_t* cylinder, tuple_t point);

#endif //RAY_TRACER_IN_C_CYLINDER_H
