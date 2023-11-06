//
// Created by ryousuke kaga on 2023/11/06.
//

#include "object.h"
#include "sphere.h"
#include "cylinder.h"
#include "group.h"
#include "algorithms/list.h"
#include "world.h"
#include "light.h"
#include "camera.h"
#include "canvas.h"

object_t hexagon_corner() {
    object_t sphere;
    sphere_init(&sphere);
    object_scale(&sphere, vector(0.25, 0.25, 0.25));
    object_translate(&sphere, vector(0, 0, -1));

    return sphere;
}

object_t hexagon_edge() {
    object_t edge;
    cylinder_data_t* cyl_data = malloc(sizeof(cylinder_data_t));
    cyl_data->minimum = 0;
    cyl_data->maximum = 1;
    cyl_data->closed = 0;
    cylinder_init(&edge, cyl_data);

    return edge;
}

object_t hexagon_side() {
    object_t side;
    List* side_objs = malloc(sizeof(List));
    list_init(side_objs, NULL);
    group_data_t* side_data = malloc(sizeof(group_data_t));
    side_data->objects = side_objs;
    group_init(&side, side_data);

    object_t* corner = malloc(sizeof(object_t));
    object_t* edge = malloc(sizeof(object_t));

    *corner = hexagon_corner();
    *edge = hexagon_edge();

    group_add_object(&side, corner);
    group_add_object(&side, edge);

    return side;
}

int main() {
    object_t hex;
    List objects;
    list_init(&objects, NULL);
    group_data_t data = {&objects};
    group_init(&hex, &data);

    for(int i=0; i < 6; i++) {
        object_t* side = malloc(sizeof(object_t));
        *side = hexagon_side();
        object_rotate_y(side, i * M_PI / 3);
        group_add_object(&hex, side);
    }

    world_t world;
    world_init(&world);

    point_light_t light = {point(-3, 3, -3), vector(1, 1, 1)};
    world.light = &light;

    world_add_object(&world, &hex);

    int width = 2000;
    int height = 2000;

    camera_t camera;
    camera_init(&camera, width, height, M_PI / 3);
    camera_transform(&camera, point(0, 1, -5), point(0, 0, 1), vector(0, 1, 0));

    int n_pixels = width * height;

    tuple_t* pixels = malloc(sizeof(tuple_t) * n_pixels);

    camera_render(&camera, &world, pixels);

    FILE* fp = fopen("hexagon_image.ppm", "w");
    canvas_write_ppm(width, height, pixels, fp);

    fclose(fp);
    free(pixels);
}