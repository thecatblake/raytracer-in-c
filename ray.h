//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_RAY_H
#define RAYTRACING_IN_C_RAY_H

#include "tuple.h"

typedef struct ray_s {
    tuple_t origin;
    tuple_t direction;
} ray_t;

#define ray(origin, direction) (ray_t){origin, direction}

tuple_t ray_position(ray_t* r, double t);
void ray_cpy(ray_t* destination, ray_t* source);

#endif //RAYTRACING_IN_C_RAY_H
