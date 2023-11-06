//
// Created by ryousuke kaga on 2023/11/06.
//

#ifndef RAY_TRACER_IN_C_INTERSECTION_H
#define RAY_TRACER_IN_C_INTERSECTION_H

#include "object.h"

typedef struct intersection_s {
    double t;
    object_t* object;
} intersection_t;

#endif //RAY_TRACER_IN_C_INTERSECTION_H
