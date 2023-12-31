//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_TESTS_H
#define RAYTRACING_IN_C_TESTS_H

#include <math.h>
#include <stdio.h>
#include "munit/munit.h"
#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "object.h"
#include "sphere.h"
#include "light.h"
#include "world.h"
#include "transformation.h"
#include "camera.h"
#include "canvas.h"
#include "plane.h"
#include "pattern.h"
#include "cube.h"
#include "cylinder.h"

#define TEST(name) MunitResult name(const MunitParameter params[], void* user_data_or_fixture)

#endif //RAYTRACING_IN_C_TESTS_H
