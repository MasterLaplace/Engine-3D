/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** Bounding Volume Hierarchy
*/

#include "engine.h"

bool cmp_av_two_triangles(triangle_t *t1, triangle_t *t2)
{
    sfVector3f s = average_triangle(t1);
    sfVector3f g = average_triangle(t2);
    return ((s.x + s.y + s.z) / 3) > ((g.x + g.y + g.z) / 3);
}

static void get_max_min_point(link_t *mesh, sfVector3f *min, sfVector3f *max)
{
    link_t *actual = mesh;
    triangle_t *tetrimi = NULL;

    if (!actual)
        return;
    do {
        tetrimi = (triangle_t *) actual->obj;
        for (int i = 0; i < 3; i++) {
            sfVector4f vertex = tetrimi->sommet[i];
            min->x = fminf(min->x, vertex.x);
            min->y = fminf(min->y, vertex.y);
            min->z = fminf(min->z, vertex.z);
            max->x = fmaxf(max->x, vertex.x);
            max->y = fmaxf(max->y, vertex.y);
            max->z = fmaxf(max->z, vertex.z);
        }
        actual = actual->next;
    } while (actual != mesh);
}

void set_bvh(Tree_t *tree, link_t *mesh)
{
    memset(tree, 0, sizeof(Tree_t));

    get_max_min_point(mesh, &tree->s_g[0], &tree->s_g[1]);

    link_t *left_up = NULL;
    link_t *right_up = NULL;

    size_t mid_len = len_link(mesh) / 2;
    size_t i = 0;

    while (mesh) {
        link_t *tmp = create_link((triangle_t *) mesh->obj);

        if (i < mid_len) {
            list_append(&left_up, tmp);
        } else {
            list_append(&right_up, tmp);
        }
        list_remove(&(mesh), mesh, NULL);
        i++;
    }

    if (left_up) {
        if (left_up->next == left_up) {
            tree->triangle = (triangle_t *) left_up->obj;
            list_remove(&left_up, left_up, NULL);
         } else {
            tree->node[0] = malloc(sizeof(Tree_t));
            set_bvh(tree->node[0], left_up);
        }
    }
    if (right_up) {
        if (right_up->next == right_up) {
            tree->triangle = (triangle_t *) right_up->obj;
            list_remove(&right_up, right_up, NULL);
         } else {
            tree->node[2] = malloc(sizeof(Tree_t));
            set_bvh(tree->node[2], right_up);
        }
    }
}

static bool is_in_triangle(sfVector4f point, triangle_t *triangle)
{
    sfVector4f v0 = triangle->sommet[1];
    sfVector4f v1 = triangle->sommet[2];
    sfVector4f v2 = triangle->sommet[0];

    // Subtract the coordinates of the third vertex from the other two vertices to get the vectors of the triangle
    v0.x -= v2.x;
    v0.y -= v2.y;
    v0.z -= v2.z;

    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;

    // Subtract the coordinates of the third vertex from the point to get a vector relative to the triangle
    sfVector4f relativePoint = point;
    relativePoint.x -= v2.x;
    relativePoint.y -= v2.y;
    relativePoint.z -=v2.z;

    // Calculate dot products between vectors in order to calculate u and v parameters for barycentric coordinates
    float dot00 = Vector_DotProduct(v0, v0);
	float dot01 = Vector_DotProduct(v0, v1);
	float dot02 = Vector_DotProduct(v0, relativePoint);
	float dot11 = Vector_DotProduct(v1, v1);
	float dot12 = Vector_DotProduct(v1, relativePoint);

    // Calculate inverse denominator for barycentric coordinates calculation and use it to calculate u and v parameters for barycentric coordinates
    float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v < 1);
}

static bool is_in_cube(sfVector4f point, sfVector3f s_g[2])
{
    return (s_g[0].x < point.x && s_g[0].y < point.y && s_g[0].z < point.z) && (s_g[1].x > point.x && s_g[1].y > point.y && s_g[1].z > point.z);
}

sfVector3f get_bvh(Tree_t *tree, sfVector4f point)
{
    sfVector3f connect_point = {0, 0, 0};
    if (tree->triangle) {
        printf("triangle : %p\n", tree->triangle);
        if (is_in_triangle(point, tree->triangle)) {
            connect_point = average_triangle(tree->triangle);
            printf("    connect_point : %f %f %f\n", connect_point.x, connect_point.y, connect_point.z);
        }
    } else {
        if (is_in_cube(point, tree->left->s_g))
            connect_point = get_bvh(tree->left, point);
        else if (is_in_cube(point, tree->right->s_g))
            connect_point = get_bvh(tree->right, point);
    }
    return connect_point;
}

void print_bvh(Tree_t *tree)
{
    if (tree->triangle) {
        printf("triangle: %f %f %f\n", tree->triangle->sommet[0].x, tree->triangle->sommet[0].y, tree->triangle->sommet[0].z);
    } else {
        if (tree->left) {
            print_bvh(tree->left);
        }
        if (tree->right) {
            print_bvh(tree->right);
        }
    }
}
