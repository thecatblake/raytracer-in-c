//
// Created by ryousuke kaga on 2023/10/30.
//

#ifndef RAY_TRACER_IN_C_WORLD_H
#define RAY_TRACER_IN_C_WORLD_H

#include "algorithms/list.h"
#include "algorithms/heap.h"
#include "matrix.h"
#include "tuple.h"
#include "ray.h"
#include "object.h"
#include "sphere.h"
#include "light.h"

typedef struct world_s {
    List objects;
    point_light_t* light;
} world_t;

typedef struct intersection_s {
    double t;
    object_t* object;
} intersection_t;

typedef struct computation_s {
    double t;
    object_t* object;
    tuple_t position;
    tuple_t over_position;
    tuple_t eyev;
    tuple_t normalv;
    int inside;
} computation_t;

void world_init(world_t* world);
Heap world_intersect(world_t* world, ray_t* ray);
int is_shadowed(world_t* world, tuple_t position);
computation_t prepare_computation(intersection_t* intersection, ray_t* ray);
tuple_t shade_hit(world_t* world, computation_t* computation);
tuple_t color_at(world_t* world, ray_t* ray);
tuple_t normal_at(object_t* object, tuple_t position);

#define world_add_object(world, object) (list_ins_next(&(world)->objects, (world)->objects.tail, (object)))

#endif //RAY_TRACER_IN_C_WORLD_H
