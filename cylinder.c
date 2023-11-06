//
// Created by ryousuke kaga on 2023/11/05.
//

#include "cylinder.h"

int check_cap(ray_t* ray, double t) {
    double x = ray->origin.x + t * ray->direction.x;
    double z = ray->origin.z + t * ray->direction.z;

    return (x * x + z * z) <= 1;
}

void cylinder_cap_hit(object_t* cylinder, ray_t* ray, double* buf, int* hit_num) {
    cylinder_data_t* cyl_data = cylinder->data;

    if(!cyl_data->closed || double_cmp2(ray->direction.y, 0)) {
        *hit_num = 0;
        return;
    }

    *hit_num = 0;

    double t = (cyl_data->minimum - ray->origin.y) / ray->direction.y;
    if(check_cap(ray, t)) {
        *hit_num += 1;
        buf[0] = t;
    }

    t = (cyl_data->maximum - ray->origin.y) / ray->direction.y;
    if(check_cap(ray, t)) {
        *hit_num += 1;
        buf[1] = t;
    }
}

void cylinder_hit(object_t* cylinder, ray_t* ray, intersection_t* buf, int* hit_num) {
    *hit_num = 0;
    cylinder_data_t *data = cylinder->data;

    int cap_hit_num;
    double cap_hits[2];
    cylinder_cap_hit(cylinder, ray, cap_hits, &cap_hit_num);

    for (int i = 0; i < cap_hit_num; i++) {
        buf[i] = (intersection_t){cap_hits[i], cylinder};
    }

    *hit_num = cap_hit_num;

    double a = ray->direction.x * ray->direction.x + ray->direction.z * ray->direction.z;

    if (double_cmp2(a, 0)) {
        return;
    }

    double b = ray->origin.x * ray->direction.x + ray->origin.z * ray->direction.z;
    double c = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - 1;

    double discriminant = b * b - a * c;

    if (discriminant < 0) {
        return;
    }

    double t0 = (-b - sqrt(discriminant)) / a;
    double t1 = (-b + sqrt(discriminant)) / a;


    double y0 = ray->origin.y + t0 * ray->direction.y;
    if (data->minimum < y0 && y0 < data->maximum) {
        buf[*hit_num] = (intersection_t){t0, cylinder};
        *hit_num += 1;
    }

    double y1 = ray->origin.y + t1 * ray->direction.y;
    if (data->minimum < y1 && y1 < data->maximum) {
        buf[*hit_num] = (intersection_t){t1, cylinder};
        *hit_num += 1;
    }
}

void cylinder_init(object_t* object, cylinder_data_t* data) {
    object_init(object);
    object->type_name = CYLINDER;
    object->data = data;
}
tuple_t cylinder_normal_at(object_t* cylinder, tuple_t point) {
    cylinder_data_t* data = cylinder->data;
    double dist = point.x * point.x + point.z * point.z;
    if(dist < 1 && point.y >= data->maximum - EPSILON_DEFAULT)
        return vector(0, 1, 0);
    if(dist < 1 && point.y <= data->minimum + EPSILON_DEFAULT)
        return vector(0, -1, 0);

    return vector(point.x, 0, point.z);
}