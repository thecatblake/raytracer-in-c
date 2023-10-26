//
// Created by ryousuke kaga on 2023/10/05.
//

#include "util.h"

int double_cmp(double a, double b, double epsilon) {
    return fabs(a-b) < epsilon;
}

int double_cmp2(double a, double b) {
    return double_cmp(a, b, EPSILON_DEFAULT);
}