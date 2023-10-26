//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_CANVAS_H
#define RAYTRACING_IN_C_CANVAS_H

#include <stdio.h>
#include <string.h>
#include "tuple.h"

void canvas_fill(int width, int height, tuple_t pixels[height][width], tuple_t color);
void canvas_write_pixel_ppm(int width, int height, tuple_t pixels[height][width], int x, int y, tuple_t color, FILE* fp);
void canvas_write_ppm(int width, int height, tuple_t pixels[height][width], FILE* fp);

#endif //RAYTRACING_IN_C_CANVAS_H
