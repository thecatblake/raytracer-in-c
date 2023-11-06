//
// Created by ryousuke kaga on 2023/11/06.
//

#include "group.h"

void group_init(object_t* object, group_data_t* data) {
    object_init(object);
    object->type_name = GROUP;
    object->data = data;
}

void group_hit(object_t* group, ray_t* ray, intersection_t* buf, int* hit_num) {
    *hit_num = 0;
    group_data_t* data = group->data;
    ListElm* objectElm = data->objects->head;

    while(objectElm) {
        object_t* object = list_data(objectElm);
        int n = 0;

        ray_t ray_inv;
        matrix_t origin_inv, direction_inv;
        matrix_inv(object->origin_transform, &origin_inv);
        matrix_inv(object->direction_transform, &direction_inv);
        ray_inv.origin = tuple_transform(origin_inv, ray->origin);
        ray_inv.direction = tuple_transform(direction_inv, ray->direction);

        switch (object->type_name) {
            case SPHERE:
            {
                sphere_hit(object, &ray_inv, &buf[*hit_num], &n);
                break;
            }
            case PLANE:
            {
                plane_hit(object, &ray_inv, &buf[*hit_num], &n);
                break;
            }
            case CUBE:
            {
                cube_hit(object, &ray_inv, &buf[*hit_num], &n);
                break;
            }
            case CYLINDER:
            {
                cylinder_hit(object, &ray_inv, &buf[*hit_num], &n);
                break;
            }
            case GROUP:
            {
                group_hit(object, &ray_inv, &buf[*hit_num], &n);
                break;
            }
            default:
                n = 0;
                break;
        }

        *hit_num += n;
        objectElm = objectElm->next;
    }
}

void group_add_object(object_t* group, object_t* object) {
    group_data_t* data = group->data;
    list_ins_next(data->objects, data->objects->tail, object);
    object->parent = group;
}

void group_object_num(object_t* group, int* out) {
    group_data_t* data = group->data;
    ListElm* objectElm = data->objects->head;

    while(objectElm) {
        object_t* object = list_data(objectElm);
        if(object->type_name == GROUP) group_object_num(object, out);
        else *out += 1;
        objectElm = objectElm->next;
    }
}