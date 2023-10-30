//
// Created by ryousuke kaga on 2023/10/05.
//

#include "canvas.h"
#include <stdlib.h>

void canvas_fill(int width, int height, tuple_t* pixels, tuple_t color) {
    for(int y=0; y < height; y++) {
        for(int x=0; x < width; x++) {
            pixels[y * width + x] = color;
        }
    }
}

void canvas_write_ppm(int width, int height, tuple_t* pixels, FILE* fp) {
    // 1 pixel occupies 12 bytes.
    // each row takes width * 12 + 1 bytes
    // header occupies 17 bytes.
    char* ppm = malloc(13 + (width * 12 + 1) * height + 1 + 1);
    char *p = ppm;
    sprintf(ppm, "P3\n%.4d %.4d\n255\n", width, height);
    p += 17;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int x = (int)(pixels[i * height + j].x * 255);
            int y = (int)(pixels[i * height + j].y * 255);
            int z = (int)(pixels[i * height + j].z * 255);
            x = x < 999 && x >= 0 ? x : 0;
            y = y < 999 && y >= 0 ? y : 0;
            z = z < 999 && z >= 0 ? z : 0;
            sprintf(p, "%.3d %.3d %.3d ", x, y, z);
            p += 12;
        }
        *p = '\n';
        p += 1;
    }

    *p = '\n';
    fwrite(ppm, strlen(ppm), 1, fp);
    free(ppm);
}