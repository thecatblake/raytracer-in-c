//
// Created by ryousuke kaga on 2023/10/05.
//

#include "canvas.h"
#include <stdlib.h>

void canvas_fill(int width, int height, tuple_t pixels[height][width], tuple_t color) {
    for(int y=0; y < height; y++) {
        for(int x=0; x < width; x++) {
            pixels[y][x] = color;
        }
    }
}

void canvas_write_pixel_ppm(int width, int height, tuple_t pixels[height][width], int x, int y, tuple_t color, FILE* fp) {

}