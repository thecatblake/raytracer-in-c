//
// Created by ryousuke kaga on 2023/11/05.
//

#ifndef RAY_TRACER_IN_C_CYLINDER_H
#define RAY_TRACER_IN_C_CYLINDER_H

#include "tuple.h"
#include "ray.h"
#include "object.h"

typedef struct cylinder_data_s {
    double minimum;
    double maximum;
    int closed;
} cylinder_data_t;

void cylinder_hit(object_t* cylinder, ray_t* ray, double* buf, int* hit_num);
void cylinder_init(object_t* object, cylinder_data_t* data);
tuple_t cylinder_normal_at(object_t* cylinder, tuple_t point);

#endif //RAY_TRACER_IN_C_CYLINDER_H
