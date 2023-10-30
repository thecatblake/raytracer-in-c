//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_CANVAS_H
#define RAYTRACING_IN_C_CANVAS_H

#include <stdio.h>
#include <string.h>
#include "tuple.h"

void canvas_fill(int width, int height, tuple_t* pixels, tuple_t color);
void canvas_write_ppm(int width, int height, tuple_t* pixels, FILE* fp);

#endif //RAYTRACING_IN_C_CANVAS_H
