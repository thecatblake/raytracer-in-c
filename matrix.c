//
// Created by ryousuke kaga on 2023/10/05.
//

#include "matrix.h"

matrix_t* matrix_zero(matrix_t* m) {
    for(int i=0; i < 16; i++) {
        (*m)[i] = 0;
    }
    return m;
}

double matrix_at(const matrix_t m, int x, int y) {
    return m[y*4+x];
}

void matrix_set(matrix_t m, int x, int y, double f) {
    m[y*4+x] = f;
}

int matrix_cmp(matrix_t a, matrix_t b, double delta) {
    for(int i=0; i < 16; i++) {
        if(double_cmp(a[i], b[i], delta)) continue;
        else return 0;
    }
    return 1;
}

int matrix_cmp2(matrix_t a, matrix_t b) {
    return matrix_cmp(a, b, EPSILON_DEFAULT);
}

matrix_t* matrix_add(const matrix_t a, const matrix_t b, matrix_t* buf) {
    for(int i=0; i<16; i++) {
        (*buf)[i] = a[i] + b[i];
    }
    return buf;
}

matrix_t* matrix_mul(const matrix_t a, const matrix_t b, matrix_t* buf) {
    matrix_t tmp = {
            a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12],
            a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13],
            a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14],
            a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15],
            a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12],
            a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13],
            a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14],
            a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15],
            a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12],
            a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13],
            a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14],
            a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15],
            a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12],
            a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13],
            a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14],
            a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15]
    };

    matrix_cpy(*buf, tmp);
    return buf;
}

matrix_t* tuple_to_matrix(tuple_t* t, matrix_t* buf) {
    matrix_set(*buf, 0, 0, t->x);
    matrix_set(*buf, 1, 1, t->y);
    matrix_set(*buf, 2, 2, t->z);
    matrix_set(*buf, 3, 3, t->w);
    return buf;
}

tuple_t matrix_to_tuple(matrix_t m) {
    return tuple(matrix_at(m, 0, 0), matrix_at(m, 1, 1), matrix_at(m, 2, 2), matrix_at(m, 3, 3));
}

matrix_t* matrix_id(matrix_t* buf) {
    matrix_zero(buf);
    for(int i=0; i < 4; i++) {
        matrix_set(*buf, i, i, 1);
    }
    return buf;
}

matrix_t* matrix_T(const matrix_t m, matrix_t* buf) {
    matrix_t tmp;
    for(int i=0; i<16;i++) {
        tmp[4*(i%4) + i/4] = m[i];
    }
    matrix_cpy(*buf, tmp);
    return buf;
}

double matrix_det(const matrix_t m) {
    return m[0] *(m[5]  * m[10] * m[15] -
                  m[5]  * m[11] * m[14] -
                  m[9]  * m[6]  * m[15] +
                  m[9]  * m[7]  * m[14] +
                  m[13] * m[6]  * m[11] -
                  m[13] * m[7]  * m[10]) +
           m[1] *(-m[4]  * m[10] * m[15] +
                  m[4]  * m[11] * m[14] +
                  m[8]  * m[6]  * m[15] -
                  m[8]  * m[7]  * m[14] -
                  m[12] * m[6]  * m[11] +
                  m[12] * m[7]  * m[10]) +
           m[2]* (m[4]  * m[9] * m[15] -
                  m[4]  * m[11] * m[13] -
                  m[8]  * m[5] * m[15] +
                  m[8]  * m[7] * m[13] +
                  m[12] * m[5] * m[11] -
                  m[12] * m[7] * m[9]) +
           m[3] * (-m[4]  * m[9] * m[14] +
                   m[4]  * m[10] * m[13] +
                   m[8]  * m[5] * m[14] -
                   m[8]  * m[6] * m[13] -
                   m[12] * m[5] * m[10] +
                   m[12] * m[6] * m[9]);
}

int matrix_is_invertible(matrix_t m) {
    return matrix_det(m) != 0;
}

matrix_t* matrix_inv(const matrix_t  m, matrix_t* buf) {
    double inv[16], det;

    inv[0] = m[5]  * m[10] * m[15] -
             m[5]  * m[11] * m[14] -
             m[9]  * m[6]  * m[15] +
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] -
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] +
             m[4]  * m[11] * m[14] +
             m[8]  * m[6]  * m[15] -
             m[8]  * m[7]  * m[14] -
             m[12] * m[6]  * m[11] +
             m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] -
             m[4]  * m[11] * m[13] -
             m[8]  * m[5] * m[15] +
             m[8]  * m[7] * m[13] +
             m[12] * m[5] * m[11] -
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] +
              m[4]  * m[10] * m[13] +
              m[8]  * m[5] * m[14] -
              m[8]  * m[6] * m[13] -
              m[12] * m[5] * m[10] +
              m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] +
             m[1]  * m[11] * m[14] +
             m[9]  * m[2] * m[15] -
             m[9]  * m[3] * m[14] -
             m[13] * m[2] * m[11] +
             m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] -
             m[0]  * m[11] * m[14] -
             m[8]  * m[2] * m[15] +
             m[8]  * m[3] * m[14] +
             m[12] * m[2] * m[11] -
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] +
             m[0]  * m[11] * m[13] +
             m[8]  * m[1] * m[15] -
             m[8]  * m[3] * m[13] -
             m[12] * m[1] * m[11] +
             m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] -
              m[0]  * m[10] * m[13] -
              m[8]  * m[1] * m[14] +
              m[8]  * m[2] * m[13] +
              m[12] * m[1] * m[10] -
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] -
             m[1]  * m[7] * m[14] -
             m[5]  * m[2] * m[15] +
             m[5]  * m[3] * m[14] +
             m[13] * m[2] * m[7] -
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] +
             m[0]  * m[7] * m[14] +
             m[4]  * m[2] * m[15] -
             m[4]  * m[3] * m[14] -
             m[12] * m[2] * m[7] +
             m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] -
              m[0]  * m[7] * m[13] -
              m[4]  * m[1] * m[15] +
              m[4]  * m[3] * m[13] +
              m[12] * m[1] * m[7] -
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] +
              m[0]  * m[6] * m[13] +
              m[4]  * m[1] * m[14] -
              m[4]  * m[2] * m[13] -
              m[12] * m[1] * m[6] +
              m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
             m[1] * m[7] * m[10] +
             m[5] * m[2] * m[11] -
             m[5] * m[3] * m[10] -
             m[9] * m[2] * m[7] +
             m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
             m[0] * m[7] * m[10] -
             m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] -
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
              m[0] * m[7] * m[9] +
              m[4] * m[1] * m[11] -
              m[4] * m[3] * m[9] -
              m[8] * m[1] * m[7] +
              m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
              m[0] * m[6] * m[9] -
              m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if(det == 0) {
        return NULL;
    }

    det = 1.0 / det;

    for (int i = 0; i < 16; i++)
        (*buf)[i] = inv[i] * det;
    return buf;
}

void matrix_cpy(matrix_t destination, const matrix_t source) {
    for(int i=0; i<16; i++) {
        destination[i] = source[i];
    }
}

tuple_t tuple_transform(const matrix_t m, tuple_t t) {
    return tuple(m[0] * t.x + m[1] * t.y + m[2] * t.z + m[3] * t.w,
                 m[4] * t.x + m[5] * t.y + m[6] * t.z + m[7] * t.w,
                 m[8] * t.x + m[9] * t.y + m[10] * t.z + m[11] * t.w,
                 m[12] * t.x + m[13] * t.y + m[14] * t.z + m[15] * t.w);
}

matrix_t* translation_matrix(double x, double y, double z, matrix_t* buf) {
    matrix_t m = {1, 0, 0, x,
                  0, 1, 0, y,
                  0, 0, 1, z,
                  0, 0, 0, 1};
    matrix_cpy(*buf, m);
    return buf;
}

matrix_t* scaling_matrix(double x, double y, double z, matrix_t* buf) {
    matrix_t m = {x, 0, 0, 0,
                  0, y, 0, 0,
                  0, 0, z, 0,
                  0, 0, 0, 1};
    matrix_cpy(*buf, m);
    return buf;
}

matrix_t* rotation_x_matrix(double rad, matrix_t* buf) {
    matrix_t m = {1, 0, 0, 0,
                  0, cos(rad), -sin(rad), 0,
                  0, sin(rad), cos(rad), 0,
                  0, 0, 0, 1};
    matrix_cpy(*buf, m);
    return buf;
}

matrix_t* rotation_y_matrix(double rad, matrix_t* buf) {
    matrix_t m = {cos(rad), 0, sin(rad), 0,
                  0, 1, 0, 0,
                  -sin(rad), 0, cos(rad), 0,
                  0, 0, 0, 1};
    matrix_cpy(*buf, m);
    return buf;
}

matrix_t* rotation_z_matrix(double rad, matrix_t* buf) {
    matrix_t m = {cos(rad), -sin(rad), 0, 0,
                  sin(rad), cos(rad), 0, 0,
                 0, 0, 1, 0,
                  0, 0, 0, 1};
    matrix_cpy(*buf, m);
    return buf;
}