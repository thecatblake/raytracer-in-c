//
// Created by ryousuke kaga on 2023/10/30.
//

#include "light.h"

tuple_t lighting(material_t* material, point_light_t* light, tuple_t position, tuple_t eyev, tuple_t normalv) {
    tuple_t e_c, lightv, reflectv;

    e_c = tuple_mul(material->color, light->intensity);

    lightv = tuple_norm(tuple_sub(light->position, position));

    tuple_t ambient, diffuse, specular;
    ambient = tuple_sc_mul(e_c, material->ambient);

    double light_dot_norm = tuple_dot(lightv, normalv);

    if (light_dot_norm < 0) {
        diffuse = vector(0, 0, 0);
        specular = vector(0, 0, 0);
    } else {
        diffuse = tuple_sc_mul(e_c, material->diffuse * light_dot_norm);
        reflectv = tuple_reflect(tuple_neg(lightv), normalv);
        double reflect_dot_eye = tuple_dot(reflectv, eyev);

        if (reflect_dot_eye <= 0)
            specular = vector(0, 0, 0);
        else {
            double factor = pow(reflect_dot_eye, material->shininess);
            specular = tuple_sc_mul(light->intensity, material->specular * factor);
        }
    }

    return tuple_add(ambient, tuple_add(diffuse, specular));
}