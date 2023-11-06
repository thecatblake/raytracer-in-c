//
// Created by ryousuke kaga on 2023/11/06.
//

#ifndef RAY_TRACER_IN_C_GROUP_H
#define RAY_TRACER_IN_C_GROUP_H

#include "object.h"
#include "ray.h"
#include "algorithms/list.h"
#include "intersection.h"
#include "sphere.h"
#include "plane.h"
#include "cube.h"
#include "cylinder.h"

typedef struct group_data_s {
    List* objects;
} group_data_t;

void group_init(object_t* object, group_data_t* data);
void group_hit(object_t* group, ray_t* ray, intersection_t* buf, int* hit_num);
void group_add_object(object_t* group, object_t* object);
void group_object_num(object_t* group, int* out);


#endif //RAY_TRACER_IN_C_GROUP_H
