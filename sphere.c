//
// Created by ryousuke kaga on 2023/10/26.
//

#include "sphere.h"

void sphere_hit(object_t* sphere, ray_t* ray, intersection_t* buf, int* hit_num) {
    double a = tuple_dot(ray->direction, ray->direction);
    double b = tuple_dot(ray->origin, ray->direction);
    double c = tuple_dot(ray->origin, ray->origin) - 1;

    if(a == 0) {
        if(b == 0) {
            *hit_num = 0;
            return;
        }
        buf[0] = (intersection_t){-c / b, sphere};
        *hit_num = 1;
        return;
    }

    double discriminant = b*b - a * c;
    if(discriminant < 0) {
        *hit_num = 0;
        return;
    }

    if(discriminant == 0) {
        *hit_num = 1;
        buf[0] = (intersection_t){(-b + sqrt(discriminant)) / a, sphere};
        return;
    }

    *hit_num = 2;
    double tmp = sqrt(discriminant);
    buf[0] = (intersection_t){(-b - tmp) / a, sphere};
    buf[1] = (intersection_t){(-b + tmp) / a, sphere};
}

void sphere_init(object_t* object) {
    object_init(object);
    object->type_name = SPHERE;
}

void glass_sphere_init(object_t* object) {
    object_init(object);
    object->type_name = SPHERE;
    object->material.transparency = 1.0;
    object->material.refractive_index = 1.5;
}

tuple_t sphere_normal_at(object_t* sphere, tuple_t point) {
    return point;
}