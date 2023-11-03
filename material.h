//
// Created by ryousuke kaga on 2023/10/30.
//

#ifndef RAY_TRACER_IN_C_MATERIAL_H
#define RAY_TRACER_IN_C_MATERIAL_H

#include "tuple.h"
#include "pattern.h"

typedef struct material_s {
    tuple_t color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    double reflective;
    double transparency;
    double refractive_index;
    pattern_t pattern;
} material_t;

void material_init(material_t* material);

#endif //RAY_TRACER_IN_C_MATERIAL_H
