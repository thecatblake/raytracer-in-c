//
// Created by ryousuke kaga on 2023/10/26.
//

#include "sphere.h"

void sphere_hit(ray_t* ray, double* buf, int* hit_num) {
    double a = tuple_dot(ray->direction, ray->direction);
    double b = tuple_dot(ray->origin, ray->direction);
    double c = tuple_dot(ray->origin, ray->origin) - 1;

    if(a == 0) {
        if(b == 0) {
            *hit_num = 0;
            return;
        }
        buf[0] = -c/b;
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
        buf[0] = (-b + sqrt(discriminant)) / a;
        return;
    }

    *hit_num = 2;
    double tmp = sqrt(discriminant);
    buf[0] = (-b - tmp) / a;
    buf[1] = (-b + tmp) / a;
}