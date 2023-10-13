/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** world_mapper
*/

const unsigned CHUNCK_SIZE = 10;

/**
 * @brief RULE:
 * 1. The map is a 2D array of chunck
 * 2. A chunck is fill of mesh (3D object) and don't cut the mesh
 * 3. A chunck is a Quadtree of mesh (3D object)
 */

const world_t world = {
    .map = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0,},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    },
    .map_size = {10, 10},
    .map_pos = {0, 0},
    .map_pos_max = {0, 0},
    .map_pos_min = {0, 0},
    .map_pos_offset = {0, 0},
    .map_pos_offset_max = {0, 0},
    .map_pos_offset_min = {0, 0},
    .map_pos_offset_max_x = 0,
    .map_pos_offset_max_y = 0,
    .map_pos_offset_min_x = 0,
    .map_pos_offset_min_y = 0,
    .map_pos_offset_x = 0,
    .map_pos_offset_y = 0,
    .map_pos_offset_z = 0,
    .map_pos_offset_max_z = 0,
    .map_pos_offset_min_z = 0,
    .map_pos_offset_max_z_x = 0,
    .map_pos_offset_max_z_y = 0,
    .map_pos_offset_min_z_x = 0,
    .map_pos_offset_min_z_y = 0
}