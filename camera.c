//
// Created by ryousuke kaga on 2023/10/31.
//

#include "camera.h"

void camera_init(camera_t* camera, int hsize, int vsize, double field_of_view) {
    camera->hsize = hsize;
    camera->vsize = vsize;
    camera->field_of_view = field_of_view;
    double half_view = tan(camera->field_of_view / 2);
    double aspect = (double)camera->hsize / camera->vsize;

    if (aspect >= 1) {
        camera->half_width = half_view;
        camera->half_height = half_view / aspect;
    } else {
        camera->half_width = half_view * aspect;
        camera->half_height = half_view;
    }

    camera->pixel_size = (camera->half_width * 2) / camera->hsize;

    matrix_id(&camera->transform);
}

void camera_render(camera_t* camera, world_t* world, tuple_t* pixels) {
    ray_t ray;
    tuple_t color;
    for (int y=0; y < camera->vsize; y++) {
        for (int x=0; x < camera->hsize; x++) {
            ray = ray_for_pixel(camera, x, y);
            color = color_at(world, &ray, 5);
            pixels[y * camera->vsize + x] = color;
        }
    }
}

void camera_transform(camera_t* camera, tuple_t from, tuple_t to, tuple_t up) {
    matrix_t temp;
    view_transform(from, to, up, &temp);
    add_transform(camera->transform, temp, &camera->transform);
}

ray_t ray_for_pixel(camera_t* camera, int px, int py) {
    double xoffset = (px + 0.5) * camera->pixel_size;
    double yoffset = (py + 0.5) * camera->pixel_size;
    double world_x = camera->half_width - xoffset;
    double world_y = camera->half_height - yoffset;

    matrix_t temp;
    tuple_t pixel = tuple_transform(*matrix_inv(camera->transform, &temp), point(world_x, world_y, -1));
    tuple_t origin = tuple_transform(*matrix_inv(camera->transform, &temp), point(0, 0, 0));
    tuple_t direction = tuple_norm(tuple_sub(pixel, origin));

    return (ray_t){origin, direction};
}