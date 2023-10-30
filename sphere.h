//
// Created by ryousuke kaga on 2023/10/26.
//

#ifndef RAY_TRACER_IN_C_SPHERE_H
#define RAY_TRACER_IN_C_SPHERE_H

#include "ray.h"
#include "object.h"

void sphere_hit(ray_t* ray, double* buf, int* hit_num);
tuple_t sphere_normal_at(object_t* sphere, tuple_t point);

#endif //RAY_TRACER_IN_C_SPHERE_H
