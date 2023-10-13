/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** quadtree
*/

/**
 * @brief  Quadtree is a tree data structure in which each internal node has exactly four children.
 *
 * @param parent - parent node
 * @param children - 0 = top left, 1 = top right, 2 = bottom left, 3 = bottom right
 * @param mesh - list of mesh
 * @param pos_max - corner max (top right)
 * @param pos_min - corner min (bottom left)
 *
 * (pos_max - pos_min)/2 = center of the quadtree
 */
typedef struct quadtree_s {
    struct quadtree_s *parent;
    struct quadtree_s *children[4];
    link_t *mesh;
    sfVector3f pos_max;
    sfVector3f pos_min;
} quadtree_t;

quadtree_t *create_quadtree(sfVector2f pos_max, sfVector2f pos_min)
{
    quadtree_t *quadtree = malloc(sizeof(quadtree_t));

    quadtree->parent = NULL;
    quadtree->children[0] = NULL;
    quadtree->children[1] = NULL;
    quadtree->children[2] = NULL;
    quadtree->children[3] = NULL;
    quadtree->mesh = NULL;
    quadtree->pos_max = pos_max;
    quadtree->pos_min = pos_min;
    return quadtree;
}

void add_in_quadtree(quadtree_t *quadtree, link_t *mesh)
{
    if (quadtree->children[0] == NULL) {
        list_append(&(quadtree->mesh), mesh);
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (mesh->pos.x > quadtree->children[i]->pos_max.x ||
            mesh->pos.x < quadtree->children[i]->pos_min.x ||
            mesh->pos.y > quadtree->children[i]->pos_max.y ||
            mesh->pos.y < quadtree->children[i]->pos_min.y ||
            mesh->pos.z > quadtree->children[i]->pos_max.z ||
            mesh->pos.z < quadtree->children[i]->pos_min.z)
            continue;
        add_in_quadtree(quadtree->children[i], mesh);
    }
}
