/*
** EPITECH PROJECT, 2024
** Engine-3D
** File description:
** WorldPartition
*/

#ifndef WORLDPARTITION_H_
#define WORLDPARTITION_H_

#include "engine.h"

// bool is_sphere_triangle_collision(sfVector4f sphere_center, float sphere_radius, triangle_t triangle);

// sfVector4f resolve_sphere_triangle_collision(sfVector4f sphere_center, float sphere_radius, triangle_t triangle);

typedef struct rectangle_s {
    sfVector3f pos;
    sfVector3f size;
} rectangle_t; // AABB

typedef struct octree_s {
    rectangle_t box;
    rectangle_t children_box[8];
    struct octree_s *children[8];
    triangle_t *data; // vector of triangles
    unsigned data_size;
    unsigned depth;
} octree_t;

#define MAX_DEPTH 8

rectangle_t get_size_of_mesh(link_t *mesh);

octree_t *octree_create(rectangle_t box, unsigned depth);

void octree_resize(octree_t *o, rectangle_t box);

void octree_clear(octree_t *o);

unsigned octree_size(octree_t *o);

// Function to check if a point is inside a rectangle (AABB)
bool point_inside_rectangle(sfVector4f point, rectangle_t rect);

// Function to check if a triangle is inside a rectangle (AABB)
bool rectangle_contains_triangle(rectangle_t box, triangle_t tri);

// Function to check if a line segment intersects with an AABB
bool line_segment_intersects_aabb(sfVector4f p1, sfVector4f p2, rectangle_t rect);

// Function to check if a triangle overlaps with an AABB
bool rectangle_overlaps_triangle(rectangle_t box, triangle_t tri);

void octree_insert(octree_t *o, triangle_t tri);

bool rectangle_contains_point(rectangle_t box, sfVector4f point);

void octree_fill(octree_t *tree, link_t *mesh);

void octree_check_collision(octree_t *tree, sfVector4f *sphere_center, float sphere_radius);

void octree_destroy(octree_t *octree);

typedef struct r_tree_s {
    sfVector2f pos;
    sfVector2f size;
    struct r_tree_s *children[4];
    link_t *data; // list of octree_t
} r_tree_t;

r_tree_t *r_tree_create(sfVector2f pos, sfVector2f size);

void r_tree_fill(r_tree_t *r_tree, link_t *octrees);

void r_tree_check_collision(r_tree_t *r_tree, sfVector4f *sphere_center, float sphere_radius);

void r_tree_destroy(r_tree_t *r_tree);

#define CHUNK_SIZE 100

typedef struct {
    sfVector2f pos;
    sfVector2f size;
    bool loaded;
    r_tree_t *data;
} chunk_t;

typedef struct world_partition_s {
    sfVector2f world_size;
    sfVector2f world_position;
    sfVector2f chunk_size;
    chunk_t *chunks;
} world_partition_t;

world_partition_t *init_world(sfVector2f chunk_size);

world_partition_t *world_partition_create(sfVector2f world_size, sfVector2f chunk_size, sfVector2f start_position);

void world_partition_destroy(world_partition_t *partition);

void world_partition_update(world_partition_t *partition, sfVector2f position, float radius);

void world_partition_load_chunk(world_partition_t *partition, sfVector2f position);

void world_partition_unload_chunk(world_partition_t *partition, sfVector2f position);

bool world_partition_is_chunk_loaded(world_partition_t *partition, sfVector2f position);

void world_partition_set_chunk_data(world_partition_t *partition, sfVector2f position, r_tree_t *data);

r_tree_t *world_partition_get_chunk_data(world_partition_t *partition, sfVector2f position);

/** Collision Pipeline - All steps:
 * 1.  init_world                           // validé
 * 2.  octree_create
 * 3.  octree_fill
 * 4.  world_partition_create               // validé
 * 5.  world_partition_update               // validé
 * 6.  world_partition_load_chunk
 * 7.  r_tree_create
 * 8.  r_tree_fill
 * 9.  world_partition_get_chunk_data       // validé
 * 10. r_tree_check_collision
 * 11. octree_check_collision
 * 12. is_sphere_triangle_collision         // validé
 * 13. resolve_sphere_triangle_collision    // validé
 * 14. world_partition_unload_chunk
 * 15. world_partition_destroy
 * 16. free_world
*/

#endif /* !WORLDPARTITION_H_ */
