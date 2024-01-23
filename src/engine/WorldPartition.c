/*
** EPITECH PROJECT, 2024
** Engine-3D
** File description:
** WorldPartition
*/

#include "WorldPartition.h"

static bool is_sphere_triangle_collision(sfVector4f sphere_center, float sphere_radius, triangle_t triangle)
{
    sfVector4f triangle_normal = Vector_CrossProduct(Vector_Sub(triangle.sommet[1], triangle.sommet[0]), Vector_Sub(triangle.sommet[2], triangle.sommet[0]));
    triangle_normal = Vector_Normalise(triangle_normal);

    float signed_distance = Vector_DotProduct(Vector_Sub(sphere_center, triangle.sommet[0]), triangle_normal);
    if (fabs(signed_distance) > sphere_radius)
        return false;

    for (int i = 0; i < 3; i++) {
        sfVector4f edge_start = triangle.sommet[i];
        sfVector4f edge_end = triangle.sommet[(i + 1) % 3];

        sfVector4f edge_direction = Vector_Sub(edge_end, edge_start);
        float edge_projection = Vector_DotProduct(Vector_Sub(sphere_center, edge_start), edge_direction) / Vector_DotProduct(edge_direction, edge_direction);
        sfVector4f closest_point_on_edge = Vector_Add(edge_start, Vector_Mul(edge_direction, edge_projection));

        if (0 <= edge_projection && edge_projection <= 1 && Vector_Length(Vector_Sub(closest_point_on_edge, sphere_center)) < sphere_radius)
            return true;
    }
    return false;
}

static sfVector4f resolve_sphere_triangle_collision(sfVector4f sphere_center, float sphere_radius, triangle_t triangle)
{
    sfVector4f triangle_normal = Vector_CrossProduct(Vector_Sub(triangle.sommet[1], triangle.sommet[0]), Vector_Sub(triangle.sommet[2], triangle.sommet[0]));
    triangle_normal = Vector_Normalise(triangle_normal);

    float signed_distance = Vector_DotProduct(Vector_Sub(sphere_center, triangle.sommet[0]), triangle_normal);

    if (fabs(signed_distance) < sphere_radius) {
        float penetration_depth = sphere_radius - fabs(signed_distance);

        sfVector4f penetration_vector = Vector_Mul(triangle_normal, penetration_depth);

        if (signed_distance < 0)
            return Vector_Sub(sphere_center, penetration_vector);

        return Vector_Add(sphere_center, penetration_vector);
    }
    return sphere_center;
}

rectangle_t get_size_of_mesh(link_t *mesh)
{
    link_t *actual_tri = mesh;
    triangle_t *tri = NULL;
    rectangle_t box = {0};


    if (actual_tri == NULL)
        return (box);
    do {
        tri = (triangle_t *) actual_tri->obj;

        for (int i = 0; i < 3; i++) {
            if (tri->sommet[i].x < box.pos.x)
                box.pos.x = tri->sommet[i].x;
            if (tri->sommet[i].y < box.pos.y)
                box.pos.y = tri->sommet[i].y;
            if (tri->sommet[i].z < box.pos.z)
                box.pos.z = tri->sommet[i].z;
            if (tri->sommet[i].x > box.pos.x + box.size.x)
                box.size.x = tri->sommet[i].x - box.pos.x;
            if (tri->sommet[i].y > box.pos.y + box.size.y)
                box.size.y = tri->sommet[i].y - box.pos.y;
            if (tri->sommet[i].z > box.pos.z + box.size.z)
                box.size.z = tri->sommet[i].z - box.pos.z;
        }

        actual_tri = actual_tri->next;
    } while (mesh && actual_tri != mesh);

    return (box);
}

octree_t *octree_create(rectangle_t box, unsigned depth)
{
    octree_t *o = (octree_t*)malloc(sizeof(octree_t));
    for (int i = 0; i < 8; i++)
        o->children[i] = NULL;
    o->data = NULL;
    o->data_size = 0;
    o->depth = depth;
    octree_resize(o, box);
    return (o);
}

void octree_resize(octree_t *o, rectangle_t box)
{
    octree_clear(o);
    o->box = box;
    sfVector3f pos2 = {box.pos.x + box.size.x / 2, box.pos.y + box.size.y / 2, box.pos.z + box.size.z / 2};

    // top left front
    o->children_box[0] = (rectangle_t){box.pos, (sfVector3f){box.size.x / 2, box.size.y / 2, box.size.z / 2}};
    // top right front
    o->children_box[1] = (rectangle_t){(sfVector3f){pos2.x, box.pos.y, box.pos.z}, (sfVector3f){box.size.x / 2, box.size.y / 2, box.size.z / 2}};
    // top left back
    o->children_box[2] = (rectangle_t){(sfVector3f){box.pos.x, box.pos.y, pos2.z}, (sfVector3f){box.size.x / 2, box.size.y / 2, box.size.z / 2}};
    // top right back
    o->children_box[3] = (rectangle_t){(sfVector3f){pos2.x, box.pos.y, pos2.z}, (sfVector3f){box.size.x / 2, box.size.y / 2, box.size.z / 2}};
    // bottom left front
    o->children_box[4] = (rectangle_t){(sfVector3f){box.pos.x, pos2.y, box.pos.z}, (sfVector3f){box.size.x / 2, box.size.y / 2, box.size.z / 2}};
    // bottom right front
    o->children_box[5] = (rectangle_t){(sfVector3f){pos2.x, pos2.y, box.pos.z}, (sfVector3f){box.size.x / 2, box.size.y / 2, box.size.z / 2}};
    // bottom left back
    o->children_box[6] = (rectangle_t){(sfVector3f){box.pos.x, pos2.y, pos2.z}, (sfVector3f){box.size.x / 2, box.size.y / 2, box.size.z / 2}};
    // bottom right back
    o->children_box[7] = (rectangle_t){(sfVector3f){pos2.x, pos2.y, pos2.z}, (sfVector3f){box.size.x / 2, box.size.y / 2, box.size.z / 2}};
}

void octree_clear(octree_t *o)
{
    if (o->data) {
        free(o->data);
        o->data = NULL;
    }
    for (unsigned i = 0; i < 8; i++) {
        if (o->children[i]) {
            octree_clear(o->children[i]);
            free(o->children[i]);
            o->children[i] = NULL;
        }
    }
}

unsigned octree_size(octree_t *o)
{
    unsigned size = 0;
    if (o->data)
        size += o->data_size;
    for (unsigned i = 0; i < 8; i++)
        if (o->children[i])
            size += octree_size(o->children[i]);
    return (size);
}

// Function to check if a point is inside a rectangle (AABB)
bool point_inside_rectangle(sfVector4f point, rectangle_t rect) {
    return (point.x >= rect.pos.x && point.x <= rect.pos.x + rect.size.x &&
            point.y >= rect.pos.y && point.y <= rect.pos.y + rect.size.y &&
            point.z >= rect.pos.z && point.z <= rect.pos.z + rect.size.z);
}

// Function to check if a triangle is inside a rectangle (AABB)
bool rectangle_contains_triangle(rectangle_t box, triangle_t tri)
{
    for (int i = 0; i < 3; ++i) {
        if (!point_inside_rectangle(tri.sommet[i], box))
            return false;
    }

    return true;
}

// Function to check if a line segment intersects with an AABB
bool line_segment_intersects_aabb(sfVector4f p1, sfVector4f p2, rectangle_t rect) {
    // Check if the line segment is outside the AABB in any dimension
    if (p1.x > rect.pos.x + rect.size.x && p2.x > rect.pos.x + rect.size.x) return false;
    if (p1.x < rect.pos.x && p2.x < rect.pos.x) return false;

    if (p1.y > rect.pos.y + rect.size.y && p2.y > rect.pos.y + rect.size.y) return false;
    if (p1.y < rect.pos.y && p2.y < rect.pos.y) return false;

    if (p1.z > rect.pos.z + rect.size.z && p2.z > rect.pos.z + rect.size.z) return false;
    if (p1.z < rect.pos.z && p2.z < rect.pos.z) return false;

    return true;
}

bool rectangle_overlaps_triangle(rectangle_t box, triangle_t tri) {
    for (int i = 0; i < 3; ++i) {
        sfVector4f p1 = tri.sommet[i];
        sfVector4f p2 = tri.sommet[(i + 1) % 3];

        if (line_segment_intersects_aabb(p1, p2, box))
            return true;
    }

    for (int i = 0; i < 3; ++i) {
        sfVector4f point = tri.sommet[i];
        if (point_inside_rectangle(point, box))
            return true;
    }

    return false;
}

void octree_insert(octree_t *o, triangle_t tri)
{
    for (unsigned i = 0; i < 8; i++) {
        if (o->depth + 1 >= MAX_DEPTH)
            return;
        if (!rectangle_contains_triangle(o->children_box[i], tri))
            continue;
        if (o->children[i]) {
            octree_insert(o->children[i], tri);
            return;
        } else if (!o->children[i]) {
            o->children[i] = octree_create(o->children_box[i], o->depth + 1);
            octree_insert(o->children[i], tri);
            return;
        }
    }
    if (!o->data) {
        o->data = (triangle_t*)malloc(sizeof(triangle_t));
        o->data[0] = tri;
        o->data_size = 1;
        return;
    }
    o->data_size++;
    o->data = (triangle_t*)realloc(o->data, sizeof(triangle_t) * o->data_size);
    o->data[o->data_size - 1] = tri;
}

bool rectangle_contains_point(rectangle_t box, sfVector4f point)
{
    return (
        point.x >= box.pos.x
        && point.y >= box.pos.y
        && point.z >= box.pos.z
        && point.x <= box.pos.x + box.size.x
        && point.y <= box.pos.y + box.size.y
        && point.z <= box.pos.z + box.size.z
    );
}

void octree_fill(octree_t *tree, link_t *mesh)
{
    link_t *actual_tri = mesh;
    triangle_t *tri = NULL;

    if (actual_tri == NULL)
        return;
    do {
        tri = (triangle_t *) actual_tri->obj;

        octree_insert(tree, *tri);

        actual_tri = actual_tri->next;
    } while (mesh && actual_tri != mesh);
}

void octree_check_collision(octree_t *tree, sfVector4f *sphere_center, float sphere_radius)
{
    if (tree->data) {
        for (unsigned i = 0; i < tree->data_size; i++) {
            if (is_sphere_triangle_collision(*sphere_center, sphere_radius, tree->data[i])) {
                sfVector4f new_center = resolve_sphere_triangle_collision(*sphere_center, sphere_radius, tree->data[i]);
                sphere_center->x = new_center.x;
                sphere_center->y = new_center.y;
                sphere_center->z = new_center.z;
                engine.state = IDLE;
                engine.velocity_y = 5.f;
            }
        }
    }
    for (unsigned i = 0; i < 8; i++) {
        if (tree->children[i]) {
            if (rectangle_contains_point(tree->children_box[i], *sphere_center))
                octree_check_collision(tree->children[i], sphere_center, sphere_radius);
        }
    }
}

void octree_destroy(octree_t *octree)
{
    if (octree->data)
        free(octree->data);
    for (unsigned i = 0; i < 8; i++)
        if (octree->children[i])
            octree_destroy(octree->children[i]);
    free(octree);
}

r_tree_t *r_tree_create(sfVector2f pos, sfVector2f size)
{
    r_tree_t *r = (r_tree_t*)malloc(sizeof(r_tree_t));
    r->pos = pos;
    r->size = size;
    for (int i = 0; i < 4; i++)
        r->children[i] = NULL;
    r->data = NULL;
    return (r);
}

void r_tree_fill(r_tree_t *r_tree, link_t *octrees)
{
    link_t *actual_oct = octrees;
    octree_t *oct = NULL;
    float average_x = 0;
    float sum_x = 0;
    int count_x = 0;
    float average_y = 0;
    float sum_y = 0;
    int count_y = 0;

    if (actual_oct == NULL)
        return;
    do {
        oct = (octree_t *) actual_oct->obj;
        if (oct->box.pos.x < r_tree->pos.x || oct->box.pos.y < r_tree->pos.y
            || oct->box.pos.x + oct->box.size.x > r_tree->pos.x + r_tree->size.x
            || oct->box.pos.y + oct->box.size.y > r_tree->pos.y + r_tree->size.y)
            { // is in box
                sum_x += oct->box.pos.x;
                count_x++;
                sum_y += oct->box.pos.y;
                count_y++;
            }

        actual_oct = actual_oct->next;
    } while (octrees && actual_oct != octrees);
    average_x = sum_x / count_x;
    average_y = sum_y / count_y;

    actual_oct = octrees;
    do {
        oct = (octree_t *) actual_oct->obj;

        list_append(&(r_tree->data), create_link(oct));

        actual_oct = actual_oct->next;
    } while (octrees && actual_oct != octrees);
}

void r_tree_check_collision(r_tree_t *r_tree, sfVector4f *sphere_center, float sphere_radius)
{
    if (!r_tree)
        return;
    if (r_tree->data) {
        link_t *actual_oct = r_tree->data;
        octree_t *oct = NULL;

        if (actual_oct == NULL)
            return;
        do {
            oct = (octree_t *) actual_oct->obj;
            if (oct->box.pos.x < sphere_center->x || oct->box.pos.y < sphere_center->y
                || oct->box.pos.x + oct->box.size.x > sphere_center->x + sphere_radius
                || oct->box.pos.y + oct->box.size.y > sphere_center->y + sphere_radius)
                { // is in box
                    octree_check_collision(oct, sphere_center, sphere_radius);
                }

            actual_oct = actual_oct->next;
        } while (r_tree->data && actual_oct != r_tree->data);
    }
    for (int i = 0; i < 4; i++)
        if (r_tree->children[i])
            r_tree_check_collision(r_tree->children[i], sphere_center, sphere_radius);
}

void r_tree_destroy(r_tree_t *r_tree)
{
    while (r_tree->data)
        list_remove(&(r_tree->data), r_tree->data, NULL);
    for (int i = 0; i < 4; i++)
        if (r_tree->children[i])
            r_tree_destroy(r_tree->children[i]);
    free(r_tree);
}

world_partition_t *init_world(sfVector2f chunk_size)
{
    link_t *actual_mesh = engine.list_objs;
    mesh_t *mesh = NULL;
    sfVector2f world_position = {0, 0};
    sfVector2f world_size = {0, 0};

    if (!actual_mesh)
        return (NULL);
    do {
        mesh = (mesh_t *) actual_mesh->obj;

        if (mesh->type != MESH) {
            actual_mesh = actual_mesh->next;
            continue;
        }

        octree_t *o = octree_create(get_size_of_mesh(mesh->lTriangle), 0);
        octree_fill(o, mesh->lTriangle);
        list_append(&(engine.list_octree), create_link(o));

        link_t *actual_tri = mesh->lTriangle;
        triangle_t *tri = NULL;

        if (!actual_tri)
            return (NULL);
        do {
            tri = (triangle_t *) actual_tri->obj;

            if (tri->sommet[0].x < world_position.x)
                world_position.x = tri->sommet[0].x;
            if (tri->sommet[0].y < world_position.y)
                world_position.y = tri->sommet[0].y;
            if (tri->sommet[0].x > world_size.x)
                world_size.x = tri->sommet[0].x;
            if (tri->sommet[0].y > world_size.y)
                world_size.y = tri->sommet[0].y;

            actual_tri = actual_tri->next;
        } while (mesh->lTriangle && actual_tri != mesh->lTriangle);

        actual_mesh = actual_mesh->next;
    } while (engine.list_objs && actual_mesh != engine.list_objs);

    world_size.x -= world_position.x;
    world_size.y -= world_position.y;
    return (world_partition_create(world_size, chunk_size, world_position));
}

world_partition_t *world_partition_create(sfVector2f world_size, sfVector2f chunk_size, sfVector2f start_position)
{
    world_partition_t *partition = malloc(sizeof(world_partition_t));

    if (partition == NULL)
        return (NULL);
    partition->world_size = world_size;
    partition->chunk_size = chunk_size;
    partition->world_position = start_position;
    partition->chunks = calloc((world_size.x / chunk_size.x) * (world_size.y / chunk_size.y)+1, sizeof(chunk_t));
    if (partition->chunks == NULL) {
        free(partition);
        return (NULL);
    }

    for (int i = 0; i < (int)(world_size.x / chunk_size.x) * (world_size.y / chunk_size.y); i++) {
        partition->chunks[i].pos.x = start_position.x + (i % (int)(world_size.x / chunk_size.x)) * chunk_size.x;
        partition->chunks[i].pos.y = start_position.y + (i / (int)(world_size.x / chunk_size.x)) * chunk_size.y;
        partition->chunks[i].size = chunk_size;
        partition->chunks[i].loaded = false;
        partition->chunks[i].data = NULL;
    }
    return (partition);
}

void world_partition_destroy(world_partition_t *partition)
{
    for (int i = 0; i < (int)(partition->world_size.x / partition->chunk_size.x) * (partition->world_size.y / partition->chunk_size.y); i++) {
        if (partition->chunks[i].loaded)
            r_tree_destroy(partition->chunks[i].data);
    }
    free(partition->chunks);
    free(partition);
}

void world_partition_update(world_partition_t *partition, sfVector2f position, float radius)
{
    for (int i = 0; i < (int)((partition->world_size.x / partition->chunk_size.x) * (partition->world_size.y / partition->chunk_size.y)); i++) {
        if (partition->chunks[i].loaded) {
            if (partition->chunks[i].pos.x < position.x - radius || partition->chunks[i].pos.x > position.x + radius
                || partition->chunks[i].pos.y < position.y - radius || partition->chunks[i].pos.y > position.y  + radius) {
                printf("unload chunk: %d\n", i);
                world_partition_unload_chunk(partition, partition->chunks[i].pos);
            }
        } else {
            if (partition->chunks[i].pos.x >= position.x - radius && partition->chunks[i].pos.x <= position.x  + radius
                && partition->chunks[i].pos.y >= position.y - radius && partition->chunks[i].pos.y <= position.y  + radius) {
                printf("load chunk: %d\n", i);
                world_partition_load_chunk(partition, partition->chunks[i].pos);
            }
        }
    }
}

/** Version OPTI: load all chunks in radius looping only on chunks in radius
int index = (position.x - partition->world_position.x) / partition->chunk_size.x + (position.y - partition->world_position.y) / partition->chunk_size.y * (partition->world_size.x / partition->chunk_size.x);
if (index < 0 || index >= (partition->world_size.x / partition->chunk_size.x) * (partition->world_size.y / partition->chunk_size.y))
    return;
int nb = radius / partition->chunk_size.x + 1;

for (int i = -nb; i <= nb; i++) {
    for (int j = -nb; j <= nb; j++) {
        int index2 = index + i + j * (partition->world_size.x / partition->chunk_size.x);
        if (index2 < 0 || index2 >= (partition->world_size.x / partition->chunk_size.x) * (partition->world_size.y / partition->chunk_size.y))
            continue;
        if (partition->chunks[index2].loaded)
            continue;
        partition->chunks[index2].loaded = true;
        partition->chunks[index2].data = r_tree_create(partition->chunks[index2].pos, partition->chunks[index2].size);
        r_tree_fill(partition->chunks[index2].data, engine.list_objs);
    }
}
*/

void world_partition_load_chunk(world_partition_t *partition, sfVector2f position)
{
    int index = (
          (position.x - partition->world_position.x) / partition->chunk_size.x
        + (position.y - partition->world_position.y) / partition->chunk_size.y
        * (partition->world_size.x / partition->chunk_size.x) - 1
    );

    if (index < 0 || index >= (partition->world_size.x / partition->chunk_size.x) * (partition->world_size.y / partition->chunk_size.y))
        return;
    if (partition->chunks[index].loaded)
        return;
    partition->chunks[index].loaded = true;
    partition->chunks[index].data = r_tree_create(partition->chunks[index].pos, partition->chunks[index].size);
    r_tree_fill(partition->chunks[index].data, engine.list_octree);
}

void world_partition_unload_chunk(world_partition_t *partition, sfVector2f position)
{
    int index = (
          (position.x - partition->world_position.x) / partition->chunk_size.x
        + (position.y - partition->world_position.y) / partition->chunk_size.y
        * (partition->world_size.x / partition->chunk_size.x) - 1
    );

    if (index < 0 || index >= (partition->world_size.x / partition->chunk_size.x) * (partition->world_size.y / partition->chunk_size.y))
        return;
    if (!partition->chunks[index].loaded)
        return;
    partition->chunks[index].loaded = false;
    r_tree_destroy(partition->chunks[index].data);
    partition->chunks[index].data = NULL;
}

bool world_partition_is_chunk_loaded(world_partition_t *partition, sfVector2f position)
{
    int index = (
          (position.x - partition->world_position.x) / partition->chunk_size.x
        + (position.y - partition->world_position.y) / partition->chunk_size.y
        * (partition->world_size.x / partition->chunk_size.x) - 1
    );

    if (index < 0 || index >= (partition->world_size.x / partition->chunk_size.x) * (partition->world_size.y / partition->chunk_size.y))
        return (false);
    return (partition->chunks[index].loaded);
}

void world_partition_set_chunk_data(world_partition_t *partition, sfVector2f position, r_tree_t *data)
{
    int index = (
          (position.x - partition->world_position.x) / partition->chunk_size.x
        + (position.y - partition->world_position.y) / partition->chunk_size.y
        * (partition->world_size.x / partition->chunk_size.x) - 1
    );

    if (index < 0 || index >= (partition->world_size.x / partition->chunk_size.x) * (partition->world_size.y / partition->chunk_size.y))
        return;
    partition->chunks[index].data = data;
}

r_tree_t *world_partition_get_chunk_data(world_partition_t *partition, sfVector2f position)
{
    int index = (
          (position.x - partition->world_position.x) / partition->chunk_size.x
        + (position.y - partition->world_position.y) / partition->chunk_size.y
        * (partition->world_size.x / partition->chunk_size.x) - 1
    );

    if (index < 0 || index >= (partition->world_size.x / partition->chunk_size.x) * (partition->world_size.y / partition->chunk_size.y))
        return (NULL);
    return (partition->chunks[index].data);
}
