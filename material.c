//
// Created by ryousuke kaga on 2023/10/30.
//

#include "material.h"

void material_init(material_t* material) {
    material->color = vector(1, 1, 1);
    material->ambient = 0.1;
    material->specular = 0.9;
    material->diffuse = 0.9;
    material->shininess = 200.0;
    pattern_init(&material->pattern);
}