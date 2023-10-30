//
// Created by ryousuke kaga on 2023/10/30.
//

#ifndef RAY_TRACER_IN_C_LIGHT_H
#define RAY_TRACER_IN_C_LIGHT_H

#include "tuple.h"
#include "material.h"

typedef struct point_light_s {
    tuple_t position;
    tuple_t intensity;
} point_light_t;

tuple_t lighting(material_t* material, point_light_t* light, tuple_t position, tuple_t eyev, tuple_t normalv);

#endif //RAY_TRACER_IN_C_LIGHT_H
