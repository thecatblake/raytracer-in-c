//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_MATRIX_H
#define RAYTRACING_IN_C_MATRIX_H

#include <stdlib.h>
#include "tuple.h"

typedef double matrix_t[16];

matrix_t* matrix_zero(matrix_t* m);

double matrix_at(const matrix_t m, int x, int y);
void matrix_set(matrix_t m, int x, int y, double f);
int matrix_cmp(matrix_t a, matrix_t b, double delta);
int matrix_cmp2(matrix_t a, matrix_t b);
matrix_t* matrix_add(const matrix_t a, const matrix_t b, matrix_t* buf);
matrix_t* matrix_mul(const matrix_t a, const matrix_t b, matrix_t* buf);
matrix_t* tuple_to_matrix(tuple_t* t, matrix_t* buf);
tuple_t matrix_to_tuple(matrix_t m);
matrix_t* matrix_id(matrix_t* buf);
matrix_t* matrix_T(const matrix_t m, matrix_t* buf);
double matrix_det(const matrix_t m);
int matrix_is_invertible(matrix_t m);
matrix_t* matrix_inv(const matrix_t m, matrix_t* buf);
void matrix_cpy(matrix_t destination, const matrix_t source);
tuple_t tuple_transform(const matrix_t m, tuple_t t);
matrix_t* translation_matrix(double x, double y, double z, matrix_t* buf);
matrix_t* scaling_matrix(double x, double y, double z, matrix_t* buf);
matrix_t* rotation_x_matrix(double rad, matrix_t* buf);
matrix_t* rotation_y_matrix(double rad, matrix_t* buf);
matrix_t* rotation_z_matrix(double rad, matrix_t* buf);

#endif //RAYTRACING_IN_C_MATRIX_H
