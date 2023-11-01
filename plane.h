//
// Created by ryousuke kaga on 2023/11/02.
//

#ifndef RAY_TRACER_IN_C_PLANE_H
#define RAY_TRACER_IN_C_PLANE_H

#include <stdlib.h>
#include "tuple.h"
#include "matrix.h"
#include "object.h"
#include "ray.h"

void plane_init(object_t* object);
tuple_t plane_normal_at(object_t* plane, tuple_t point);
void plane_hit(ray_t* ray, double* buf, int* hit_num);

#endif //RAY_TRACER_IN_C_PLANE_H
