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
    heap_init(&intersections, intersection_compare, free);

    object_t* object;
    ListElm* object_elm = list_head(&world->objects);

    while(object_elm) {
        object = list_data(object_elm);
        double hits[2];
        int hit_num;

        switch (object->type_name) {
            case EMPTY_OBJECT:
                break;
            case SPHERE:
            {
                ray_t ray_inv;

                matrix_t origin_inv, direction_inv;
                matrix_inv(object->origin_transform, &origin_inv);
                matrix_inv(object->direction_transform, &direction_inv);
                ray_inv.origin = tuple_transform(origin_inv, ray->origin);
                ray_inv.direction = tuple_transform(direction_inv, ray->direction);
                sphere_hit(&ray_inv, hits, &hit_num);

                if (hit_num == 0)
                    break;

                double hit = hits[0];
                if (hit_num == 1 && hit < 0)
                    break;
                if (hit_num == 2 && hit <0 && hits[1] < 0)
                    break;
                if (hit_num == 2 && hit < 0 && hits[1] > 0)
                    hit = hits[1];

                intersection_t* intersection = malloc(sizeof(intersection_t));

                intersection->t = hit;
                intersection->object = object;

                heap_insert(&intersections, intersection);
                break;
            }
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

computation_t prepare_computation(intersection_t* intersection, ray_t* ray) {
    computation_t computation = {
            .t = intersection->t,
            .object = intersection->object,
            .position = ray_position(ray, intersection->t),
            .eyev = tuple_neg(ray->direction)
    };

    switch(intersection->object->type_name) {
        case EMPTY_OBJECT:
            computation.normalv = vector(0, 0, 0);
            break;
        case SPHERE:
            computation.normalv = sphere_normal_at(computation.object, computation.position);
            break;
    }

    if (tuple_dot(computation.normalv, computation.eyev) < 0) {
        computation.inside = 1;
        computation.normalv = tuple_neg(computation.normalv);
    } else
        computation.inside = 0;

    computation.over_position = tuple_add(computation.position, tuple_sc_mul(computation.normalv, EPSILON_DEFAULT));

    return computation;
}

tuple_t shade_hit(world_t* world, computation_t* computation) {
    int shadowed = is_shadowed(world, computation->over_position);
    return lighting(&computation->object->material, world->light, computation->position, computation->eyev, computation->normalv, shadowed);
}

tuple_t color_at(world_t* world, ray_t* ray) {
    Heap intersections = world_intersect(world, ray);
    intersection_t* intersection;

    if(intersections.size == 0) {
        return vector(0, 0, 0);
    }

    heap_extract(&intersections, (void**)&intersection);
    computation_t computation = prepare_computation(intersection, ray);
    tuple_t color = shade_hit(world, &computation);

    heap_destroy(&intersections);
    return color;
}