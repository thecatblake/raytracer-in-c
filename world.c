//
// Created by ryousuke kaga on 2023/10/30.
//

#include "world.h"

int intersection_compare(const void* key1, const void* key2) {
    intersection_t* is1 = (void*)key1;
    intersection_t* is2 = (void*)key2;
    return is1->t < is2->t ? 1 : -1;
}

void world_init(world_t* world) {
    list_init(&world->objects, NULL);
    world->light = NULL;
}

Heap world_intersect(world_t* world, ray_t* ray) {
    Heap intersections;
    heap_init(&intersections, intersection_compare, NULL);

    object_t* object;
    ListElm* object_elm = list_head(&world->objects);

    while(object_elm) {
        object = list_data(object_elm);
        intersection_t* hits;
        int hit_num = 0;

        ray_t ray_inv;

        matrix_t origin_inv, direction_inv;
        matrix_inv(object->origin_transform, &origin_inv);
        matrix_inv(object->direction_transform, &direction_inv);
        ray_inv.origin = tuple_transform(origin_inv, ray->origin);
        ray_inv.direction = tuple_transform(direction_inv, ray->direction);

        switch (object->type_name) {
            case EMPTY_OBJECT:
                break;
            case SPHERE:
            {
                hits = malloc(sizeof(intersection_t) * 2);
                sphere_hit(object, &ray_inv, hits, &hit_num);
                break;
            }
            case PLANE:
            {
                hits = malloc(sizeof(intersection_t) * 1);
                plane_hit(object, &ray_inv, hits, &hit_num);
                break;
            }
            case CUBE:
            {
                hits = malloc(sizeof(intersection_t) * 2);
                cube_hit(object, &ray_inv, hits, &hit_num);
                break;
            }
            case CYLINDER:
            {
                hits = malloc(sizeof(intersection_t) * 2);
                cylinder_hit(object, &ray_inv, hits, &hit_num);
                break;
            }
            case GROUP:
            {
                int n;
                group_object_num(object, &n);
                hits = malloc(sizeof(intersection_t) * n * 2);
                group_hit(object, &ray_inv, hits, &hit_num);
                break;
            }
        }

        for(int i=0; i < hit_num; i++) {
            if(hits[i].t < 0)
                continue;

            heap_insert(&intersections, &hits[i]);
        }

        object_elm = object_elm->next;
    }

    return intersections;
}

int is_shadowed(world_t* world, tuple_t position) {
    tuple_t v = tuple_sub(world->light->position, position);
    double distance = tuple_mag(v);
    tuple_t direction = tuple_norm(v);

    ray_t ray = {position, direction};
    Heap intersections = world_intersect(world, &ray);

    if(intersections.size == 0)
        return 0;

    intersection_t* intersection;
    heap_extract(&intersections, (void**)&intersection);

    if (intersection->t > distance)
        return 0;

    return 1;
}

computation_t prepare_computation(intersection_t* intersection, ray_t* ray, List* intersections) {
    computation_t computation = {
            .t = intersection->t,
            .object = intersection->object,
            .position = ray_position(ray, intersection->t),
            .eyev = tuple_neg(ray->direction)
    };

    if(intersections) {
        List objects;
        list_init(&objects, NULL);
        ListElm* intersectionElm = intersections->head;
        intersection_t* current;
        while(intersectionElm) {
            current = list_data(intersectionElm);

            if(current == intersection) {
                if (objects.size == 0)
                    computation.n1 = 1.0;
                else
                    computation.n1 = ((object_t*)list_data(objects.tail))->material.refractive_index;
            }

            ListElm temp = {NULL, objects.head};
            ListElm* objectElm = &temp;
            while(objectElm->next && ((object_t*)list_data(objectElm->next)) != current->object) {
                objectElm = objectElm->next;
            }

            void* obj_temp;

            if(!objectElm->next)
                list_ins_next(&objects, objects.tail, ((intersection_t*)intersectionElm->data)->object);
            else
                list_rem_next(&objects, objectElm, &obj_temp);

            if(current == intersection) {
                if (objects.size == 0)
                    computation.n2 = 1.0;
                else
                    computation.n2 = ((object_t*)list_data(objects.tail))->material.refractive_index;

                break;
            }

            intersectionElm = intersectionElm->next;
        }

        list_destroy(&objects);
    }

    computation.normalv = normal_at(intersection->object, computation.position);

    if (tuple_dot(computation.normalv, computation.eyev) < 0) {
        computation.inside = 1;
        computation.normalv = tuple_neg(computation.normalv);
    } else
        computation.inside = 0;

    computation.reflectv = tuple_reflect(ray->direction, computation.normalv);
    computation.over_position = tuple_add(computation.position, tuple_sc_mul(computation.normalv, EPSILON_DEFAULT));
    computation.under_position = tuple_sub(computation.position, tuple_sc_mul(computation.normalv, EPSILON_DEFAULT));
    return computation;
}

tuple_t shade_hit(world_t* world, computation_t* computation, int remaining) {
    int shadowed = is_shadowed(world, computation->over_position);
    tuple_t surface = lighting(&computation->object->material, world->light, computation->position, computation->eyev, computation->normalv, shadowed);
    tuple_t reflected = reflected_color(world, computation, remaining);
    tuple_t refracted = refracted_color(world, computation, remaining);

    material_t material = computation->object->material;

    if(material.reflective > 0 && material.transparency > 0) {
        double reflectance = schlick(computation);
        return tuple_add(surface, tuple_add(tuple_sc_mul(reflected, reflectance), tuple_sc_mul(refracted, 1 - reflectance)));
    }

    return tuple_add(surface, tuple_add(reflected, refracted));
}

tuple_t color_at(world_t* world, ray_t* ray, int remaining) {
    Heap intersections = world_intersect(world, ray);
    intersection_t* intersection;

    if(intersections.size == 0) {
        return vector(0, 0, 0);
    }

    intersection = intersections.tree[0];
    List intersectionList;
    list_init(&intersectionList, free);
    heap_to_list(&intersections, &intersectionList);
    computation_t computation = prepare_computation(intersection, ray, &intersectionList);
    intersection->object->material.color = pattern_at_object(intersection->object, computation.position);
    tuple_t color = shade_hit(world, &computation, remaining);

    heap_destroy(&intersections);
    list_destroy(&intersectionList);
    return color;
}

tuple_t pattern_at_object(object_t* object, tuple_t position) {
    matrix_t m;
    tuple_t object_point = tuple_transform(*matrix_inv(object->origin_transform, &m), position);
    tuple_t pattern_point = tuple_transform(*matrix_inv(object->material.pattern.transform, &m), object_point);

    switch (object->material.pattern.type) {
        case NO_PATTERN:
            return object->material.color;
        case STRIPE:
            return stripe_at(&object->material.pattern, pattern_point);
        case GRADIENT:
            return gradient_at(&object->material.pattern, pattern_point);
        case CHECK:
            return check_at(&object->material.pattern, pattern_point);
        case TEST:
            return testpattern_at(&object->material.pattern, pattern_point);
    }
}

tuple_t normal_at(object_t* object, tuple_t position) {
    tuple_t object_normal;

    tuple_t local_point = world_to_object(object, position);

    switch(object->type_name) {
        case SPHERE:
            object_normal = sphere_normal_at(object, local_point);
            break;
        case PLANE:
            object_normal = plane_normal_at(object, local_point);
            break;
        case CUBE:
            object_normal = cube_normal_at(object, local_point);
            break;
        case CYLINDER:
            object_normal = cylinder_normal_at(object, local_point);
            break;
        default:
            object_normal = vector(0, 0, 0);
    }

    return normal_to_world(object, object_normal);
}

tuple_t reflected_color(world_t* world, computation_t* computation, int remaining) {
    if (computation->object->material.reflective == 0 || remaining <= 0)
        return vector(0, 0, 0);

    ray_t reflect_ray = {computation->over_position, computation->reflectv};
    tuple_t color = color_at(world, &reflect_ray, remaining - 1);

    return tuple_sc_mul(color, computation->object->material.reflective);
}

tuple_t refracted_color(world_t* world, computation_t* computation, int remaining) {
    if (computation->object->material.transparency == 0 || remaining <= 0)
        return vector(0, 0, 0);

    double n_ratio = computation->n1 / computation->n2;
    double cos_i = tuple_dot(computation->eyev, computation->normalv);
    double sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);

    if (sin2_t > 1)
        return vector(0, 0, 0);

    double cos_t = sqrt(1.0 - sin2_t);
    tuple_t direction = tuple_sub(tuple_sc_mul(computation->normalv, n_ratio * cos_i - cos_t), tuple_sc_mul(computation->eyev, n_ratio));

    ray_t refract_ray = {computation->under_position, direction};
    tuple_t color = color_at(world, &refract_ray, remaining - 1);

    return tuple_sc_mul(color, computation->object->material.transparency);
}

double schlick(computation_t* computation) {
    double cos = tuple_dot(computation->eyev, computation->normalv);

    if (computation->n1 > computation->n2) {
        double n = computation->n1 / computation->n2;
        double sin2_t = n * n * (1.0 - cos * cos);
        if (sin2_t > 1.0)
            return 1.0;

        cos = sqrt(1.0 - sin2_t);
    }

    double r0 = ((computation->n1 - computation->n2) / (computation->n1 + computation->n2));
    r0 *= r0;

    return r0 + (1 - r0) * pow(1 - cos, 5);
}

tuple_t world_to_object(object_t* object, tuple_t point) {
    if(object->parent)
        point = world_to_object(object->parent, point);

    matrix_t temp;
    return tuple_transform(*matrix_inv(object->origin_transform, &temp), point);
}

tuple_t normal_to_world(object_t* object, tuple_t normal) {
    matrix_t temp;
    normal = tuple_transform(*matrix_T(*matrix_inv(object->origin_transform, &temp), &temp), normal);
    normal.w = 0;
    normal = tuple_norm(normal);

    if(object->parent)
        normal = normal_to_world(object->parent, normal);

    return normal;
}