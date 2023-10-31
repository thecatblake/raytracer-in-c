//
// Created by ryousuke kaga on 2023/10/31.
//

#ifndef RAY_TRACER_IN_C_CAMERA_H
#define RAY_TRACER_IN_C_CAMERA_H

#include "matrix.h"
#include "ray.h"
#include "world.h"

typedef struct camera_s {
    int hsize;
    int vsize;
    double field_of_view;
    double pixel_size;
    double half_width;
    double half_height;
    matrix_t transform;
} camera_t;

void camera_init(camera_t* camera, int hsize, int vsize, double field_of_view);
void camera_render(camera_t* camera, world_t* world, tuple_t* pixels);
void camera_transform(camera_t* camera, tuple_t from, tuple_t to, tuple_t up);
ray_t ray_for_pixel(camera_t* camera, int px, int py);

#endif //RAY_TRACER_IN_C_CAMERA_H
