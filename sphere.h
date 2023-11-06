//
// Created by ryousuke kaga on 2023/10/26.
//

#ifndef RAY_TRACER_IN_C_SPHERE_H
#define RAY_TRACER_IN_C_SPHERE_H

#include "ray.h"
#include "object.h"
#include "intersection.h"

void sphere_hit(object_t* sphere, ray_t* ray, intersection_t* buf, int* hit_num);
void sphere_init(object_t* object);
void glass_sphere_init(object_t* object);
tuple_t sphere_normal_at(object_t* sphere, tuple_t point);

#endif //RAY_TRACER_IN_C_SPHERE_H
