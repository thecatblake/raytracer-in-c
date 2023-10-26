//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_TUPLE_H
#define RAYTRACING_IN_C_TUPLE_H

#include "util.h"


typedef struct {
    double x;
    double y;
    double z;
    int w;
} tuple_t;

#define point(x, y, z) (tuple_t){x, y, z, 1}
#define vector(x, y, z) (tuple_t){x, y, z, 0}
#define tuple(x, y, z, w) (tuple_t){x, y, z, w}

int tuple_cmp(tuple_t t1, tuple_t t2, double delta);

int tuple_cmp2(tuple_t t1, tuple_t t2);

tuple_t tuple_add(tuple_t t1, tuple_t t2);
tuple_t tuple_sub(tuple_t t1, tuple_t t2);
tuple_t tuple_mul(tuple_t t1, tuple_t t2);

tuple_t tuple_neg(tuple_t t);

tuple_t tuple_sc_mul(tuple_t t, double s);
tuple_t tuple_sc_div(tuple_t t, double s) ;

double tuple_mag(tuple_t t);

tuple_t tuple_norm(tuple_t t);
double tuple_dot(tuple_t t1, tuple_t t2);

tuple_t tuple_cross(tuple_t t1, tuple_t t2);

void tuple_cpy(tuple_t* destination, tuple_t* source);

tuple_t tuple_reflect(tuple_t t, tuple_t n);

#endif //RAYTRACING_IN_C_TUPLE_H
