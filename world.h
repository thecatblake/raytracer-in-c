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
#include "intersection.h"
#include "sphere.h"
#include "light.h"
#include "plane.h"
#include "cube.h"
#include "cylinder.h"

typedef struct world_s {
    List objects;
    point_light_t* light;
} world_t;

typedef struct computation_s {
    double t;
    double n1;
    double n2;
    object_t* object;
    tuple_t position;
    tuple_t over_position;
    tuple_t under_position;
    tuple_t eyev;
    tuple_t normalv;
    tuple_t reflectv;
    int inside;
} computation_t;

void world_init(world_t* world);
Heap world_intersect(world_t* world, ray_t* ray);
int is_shadowed(world_t* world, tuple_t position);
computation_t prepare_computation(intersection_t* intersection, ray_t* ray, List* intersections);
tuple_t shade_hit(world_t* world, computation_t* computation, int remaining);
tuple_t color_at(world_t* world, ray_t* ray, int remaining);
tuple_t pattern_at_object(object_t* object, tuple_t position);
tuple_t normal_at(object_t* object, tuple_t position);
tuple_t reflected_color(world_t* world, computation_t* computation, int remaining);
tuple_t refracted_color(world_t* world, computation_t* computation, int remaining);
double schlick(computation_t* computation);

#define world_add_object(world, object) (list_ins_next(&(world)->objects, (world)->objects.tail, (object)))

#endif //RAY_TRACER_IN_C_WORLD_H
