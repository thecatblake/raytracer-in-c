//
// Created by ryousuke kaga on 2023/10/30.
//

#ifndef RAY_TRACER_IN_C_MATERIAL_H
#define RAY_TRACER_IN_C_MATERIAL_H

#include "tuple.h"

typedef struct material_s {
    tuple_t color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
} material_t;

void material_init(material_t* material);

#endif //RAY_TRACER_IN_C_MATERIAL_H
