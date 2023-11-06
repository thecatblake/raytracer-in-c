//
// Created by ryousuke kaga on 2023/11/04.
//

#include "cube.h"

double min(double x, double y) {
    return x < y ? x : y;
}

double max(double x, double y) {
    return x > y ? x : y;
}

void cube_hit(object_t* cube, ray_t* ray, intersection_t* buf, int* hit_num) {
    double dirfracx = 1.0f / ray->direction.x;
    double dirfracy = 1.0f / ray->direction.y;
    double dirfracz = 1.0f / ray->direction.z;
    
    double t1 = (-1 - ray->origin.x)*dirfracx;
    double t2 = (1 - ray->origin.x)*dirfracx;
    double t3 = (-1 - ray->origin.y)*dirfracy;
    double t4 = (1 - ray->origin.y)*dirfracy;
    double t5 = (-1 - ray->origin.z)*dirfracz;
    double t6 = (1 - ray->origin.z)*dirfracz;

    double tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
    double tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

    if (tmax < 0 || tmin > tmax)
    {
        *hit_num = 0;
        return;
    }

    *hit_num = 2;
    buf[0] = (intersection_t){tmin, cube};
    buf[1] = (intersection_t){tmax, cube};
}

void cube_init(object_t* object) {
    object_init(object);
    object->type_name = CUBE;
}

tuple_t cube_normal_at(object_t* cube, tuple_t point) {
    double maxc = max(fabs(point.x), max(fabs(point.y), fabs(point.z)));

    if (maxc == fabs(point.x))
        return vector(point.x, 0, 0);
    else if(maxc == fabs(point.y))
        return vector(0, point.y, 0);
    else
        return vector(0, 0, point.z);
}