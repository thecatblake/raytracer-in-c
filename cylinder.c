//
// Created by ryousuke kaga on 2023/11/05.
//

#include "cylinder.h"

void cylinder_hit(object_t* cylinder, ray_t* ray, double* buf, int* hit_num) {
    double a = ray->direction.x * ray->direction.x + ray->direction.z * ray->direction.z;

    if(double_cmp2(a, 0)) {
        *hit_num = 0;
        return;
    }

    double b = ray->origin.x * ray->direction.x + ray->origin.z * ray->direction.z;
    double c = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - 1;

    double discriminant = b * b - a * c;

    if (discriminant < 0) {
        *hit_num = 0;
        return;
    }

    *hit_num = 0;
    double t0 = (-b - sqrt(discriminant)) / a;
    double t1 = (-b + sqrt(discriminant)) / a;

    cylinder_data_t* data = cylinder->data;

    double y0 = ray->origin.y + t0 * ray->direction.y;
    if (data->minimum < y0 && y0 < data->maximum) {
        *hit_num += 1;
        buf[0] = t0;
    }

    double y1 = ray->origin.y + t1 * ray->direction.y;
    if (data->minimum < y1 && y1 < data->maximum) {
        *hit_num += 1;
        buf[1] = t1;
    }
}
void cylinder_init(object_t* object, cylinder_data_t* data) {
    object_init(object);
    object->type_name = CYLINDER;
    object->data = data;
}
tuple_t cylinder_normal_at(object_t* cylinder, tuple_t point) {
    return vector(point.x, 0, point.z);
}