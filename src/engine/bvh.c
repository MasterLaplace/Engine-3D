/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** Bounding Volume Hierarchy
*/

#include "engine.h"

bool cmp_av_two_triangles(void *t1, void *t2)
{
    sfVector3f s = average_triangle((triangle_t *)t1);
    sfVector3f g = average_triangle((triangle_t *)t2);
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
        for (unsigned i = 0; i < 3; i++) {
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

#ifdef DEBUG_MODE
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c\n"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

void print_deph(unsigned i)
{
    printf("|:");
    for (unsigned j = 0; j < i; ++j) {
        printf("-");
    }
    printf("\n");
}
#endif

static void check_recur(Tree_t *tree, link_t *list, unsigned i, unsigned len, bool ok) {
    if (list != NULL) {
        if (list->next == list || ok) {
            tree->triangle = calloc(len + 1, sizeof(triangle_t *));
            for (unsigned j = 0; list; ++j) {
                tree->triangle[j] = (triangle_t *) list->obj;
                list_remove(&list, list, NULL);
            }
        } else {
            tree->node[i] = calloc(1, sizeof(Tree_t));
            set_bvh(tree->node[i], list, len);
        }
    }
}

#ifdef DEBUG_MODE
static unsigned deph = 0;
#endif

/**
 * @brief  This function clip a triangle against a plane
 *
 * @param plane_p  A point on the plane
 * @param plane_n  The normal of the plane (Must be normalized)
 * @param lineStart  The start point of our line
 * @param lineEnd  The end point of our line
 * @return sfVector4f  The new point of the triangle
 */
sfVector4f vector_intersectPlane(sfVector4f *plane_p, sfVector4f *plane_n, sfVector4f *lineStart, sfVector4f *lineEnd)
{
    sfVector4f plane_n_norm = Vector_Normalise(*plane_n);
    float plane_d = -Vector_DotProduct(plane_n_norm, *plane_p);
    float ad = Vector_DotProduct(*lineStart, plane_n_norm);
    float bd = Vector_DotProduct(*lineEnd, plane_n_norm);
    float t = (-plane_d - ad) / (bd - ad);
    sfVector4f lineStartToEnd = Vector_Sub(*lineEnd, *lineStart);
    sfVector4f lineToIntersect = Vector_Mul(lineStartToEnd, t);
    return Vector_Add(*lineStart, lineToIntersect);
}

/**
 * @brief  This function clips a triangle against a bounding box (6 planes)
 *
 * @param triangle  The triangle to clip
 * @param s_g  The bounding box to clip against (s_g[0] = min, s_g[1] = max)
 * @param Clipped  The storage of the clipped triangles
 * @return int  The number of clipped triangles (0, 1, 2, 3, 4, 5, 6)
 */
int Triangle_ClipAgainstSG(triangle_t *triangle, sfVector3f s_g[2], triangle_t (*Clipped)[6])
{
    // Initialize a variable to keep track of the number of clipped triangles
    int numClippedTriangles = 0;

    // Clip against each of the six planes of the bounding box
    for (int i = 0; i < 6; ++i) {
        // Define the current clipping plane
        sfVector4f planeNormal = {0};
        sfVector4f planePoint = {0};

        // Define the normal and a point on the current clipping plane
        planeNormal.x = (i == 0) ? 1 : 0;
        planeNormal.y = (i == 1) ? 1 : 0;
        planeNormal.z = (i == 2) ? 1 : 0;
        planeNormal.w = 0;
        planePoint.x = (i == 0) ? s_g[1].x : s_g[0].x;
        planePoint.y = (i == 1) ? s_g[1].y : s_g[0].y;
        planePoint.z = (i == 2) ? s_g[1].z : s_g[0].z;
        planePoint.w = 1;

        // Calculate the distance from each vertex of the triangle to the current plane
        float distance[3] = {0};
        for (int j = 0; j < 3; ++j) {
            distance[j] = Vector_DotProduct(planeNormal, triangle->sommet[j]) - Vector_DotProduct(planeNormal, planePoint);
        }

        // Initialize an array to store the classification of each vertex with respect to the plane
        int classification[3] = {0};

        // Classify each vertex of the triangle with respect to the plane
        for (int j = 0; j < 3; ++j) {
            classification[j] = (distance[j] > 0) ? 1 : ((distance[j] < 0) ? -1 : 0);
        }

        // Check if the triangle has some points outside of the cube
        if (classification[0] == 0 && classification[1] == 0 && classification[2] == 0) {
            // If the triangle is inside the cube, we add it to the list of clipped triangles
            *Clipped[numClippedTriangles++] = *triangle;
            continue;
        }

        // Check if the triangle has some points inside of the cube
        if (classification[0] == 1 && classification[1] == 1 && classification[2] == 1) {
            // If the triangle is outside the cube, we discard it
            continue;
        }

        // If the triangle has some points outside and some points inside of the cube, we clip it against the current plane
        // Initialize an array to store the new vertices of the clipped triangle
        sfVector4f newVertices[3] = {0};

        // Initialize a variable to keep track of the number of vertices in the clipped triangle
        int numNewVertices = 0;

        // Loop through the vertices of the triangle
        for (int j = 0; j < 3; ++j) {
            // Store the current vertex
            sfVector4f currentVertex = triangle->sommet[j];

            // Store the next vertex
            sfVector4f nextVertex = triangle->sommet[(j + 1) % 3];

            // Check if the current vertex is inside the cube
            if (classification[j] == 1) {
                // If the current vertex is inside the cube, we add it to the list of new vertices
                newVertices[numNewVertices++] = currentVertex;
            }

            // Check if the current vertex is outside the cube
            if (classification[j] == -1) {
                // If the current vertex is outside the cube and the next vertex is inside the cube, we add the intersection point between the current edge and the current plane to the list of new vertices
                if (classification[(j + 1) % 3] == 1) {
                    // Calculate the intersection point between the current edge and the current plane
                    newVertices[numNewVertices++] = vector_intersectPlane(&planePoint, &planeNormal, &currentVertex, &nextVertex);
                }

                // If the current vertex is outside the cube and the next vertex is outside the cube, we do nothing
            }
        }

        // Check if the number of vertices in the clipped triangle is equal to 0 or 1
        if (numNewVertices == 0 || numNewVertices == 1) {
            // If the number of vertices in the clipped triangle is equal to 0 or 1, we discard it
            continue;
        }

        // Check if the number of vertices in the clipped triangle is equal to 2
        if (numNewVertices == 2) {
            // If the number of vertices in the clipped triangle is equal to 2, we create a new triangle with the two new vertices and the first vertex of the original triangle
            triangle_t clippedTriangle = {0};
            clippedTriangle.sommet[0] = newVertices[0];
            clippedTriangle.sommet[1] = newVertices[1];
            clippedTriangle.sommet[2] = triangle->sommet[0];
            clippedTriangle.usemtl = NONE;

            // Add the new triangle to the list of clipped triangles
            *Clipped[numClippedTriangles++] = clippedTriangle;
            continue;
        }

        // Check if the number of vertices in the clipped triangle is equal to 3
        if (numNewVertices == 3) {
            // If the number of vertices in the clipped triangle is equal to 3, we create a new triangle with the three new vertices
            triangle_t clippedTriangle = {0};
            clippedTriangle.sommet[0] = newVertices[0];
            clippedTriangle.sommet[1] = newVertices[1];
            clippedTriangle.sommet[2] = newVertices[2];
            clippedTriangle.usemtl = NONE;

            // Add the new triangle to the list of clipped triangles
            *Clipped[numClippedTriangles++] = clippedTriangle;
            continue;
        }

        // If the number of vertices in the clipped triangle is greater than 3, we do nothing
    }

    // Return the number of clipped triangles
    return numClippedTriangles;
}

__attribute__((optimize(0))) void set_bvh(Tree_t *tree, link_t *mesh, unsigned len)
{
    #ifdef DEBUG_MODE
    ++deph;
    print_deph(deph);
    #endif
    get_max_min_point(mesh, &tree->s_g[0], &tree->s_g[1]);
    #ifdef DEBUG_MODE
    if (-8.09411335 == tree->s_g[0].x)
        printf("min : %f, %f, %f\n", tree->s_g[0].x, tree->s_g[0].y, tree->s_g[0].z);
    #endif

    link_t *front_left_up = NULL;
    link_t *front_left_down = NULL;
    link_t *back_left_up = NULL;
    link_t *back_left_down = NULL;
    link_t *front_right_up = NULL;
    link_t *front_right_down = NULL;
    link_t *back_right_up = NULL;
    link_t *back_right_down = NULL;

    #ifdef DEBUG_MODE
    printf("--------\nlen list : %d\n--------\n", len_link(mesh));
    #endif

    while (mesh) {
        triangle_t *triangle = (triangle_t *) mesh->obj;
        // sfVector3f ta = average_triangle(triangle);

        // flu fld fru frd blu bld bru brd
        //  0   0   0   0   0   0   0   0
        // 128  64  32  16   8   4   2   1
        unsigned char pos = 0;
        // uint8_t front_left_up_c = 0;
        // uint8_t front_left_down_c = 0;
        // uint8_t front_right_up_c = 0;
        // uint8_t front_right_down_c = 0;
        // uint8_t back_left_up_c = 0;
        // uint8_t back_left_down_c = 0;
        // uint8_t back_right_up_c = 0;
        // uint8_t back_right_down_c = 0;
        for (unsigned i = 0; i < 3; ++i) {
            if ((tree->s_g[1].z-tree->s_g[0].z)/2+tree->s_g[0].z <= triangle->sommet[i].z
            && triangle->sommet[i].z <= tree->s_g[1].z) { // front
                if ((tree->s_g[1].y-tree->s_g[0].y)/2+tree->s_g[0].y <= triangle->sommet[i].y
                && triangle->sommet[i].y <= tree->s_g[1].y) { // up
                    if ((tree->s_g[1].x-tree->s_g[0].x)/2+tree->s_g[0].x <= triangle->sommet[i].x
                    && triangle->sommet[i].x <= tree->s_g[1].x) { // left
                        pos |= 1;
                        // front_left_up_c++;
                    } else { // right
                        pos |= 2;
                        // front_right_up_c++;
                    }
                } else { // down
                    if ((tree->s_g[1].x-tree->s_g[0].x)/2+tree->s_g[0].x <= triangle->sommet[i].x
                    && triangle->sommet[i].x <= tree->s_g[1].x) { // left
                        pos |= 4;
                        // front_left_down_c++;
                    } else { // right
                        pos |= 8;
                        // front_right_down_c++;
                    }
                }
            } else { // back
                if ((tree->s_g[1].y-tree->s_g[0].y)/2+tree->s_g[0].y <= triangle->sommet[i].y
                && triangle->sommet[i].y <= tree->s_g[1].y) { // up
                    if ((tree->s_g[1].x-tree->s_g[0].x)/2+tree->s_g[0].x <= triangle->sommet[i].x
                    && triangle->sommet[i].x <= tree->s_g[1].x) { // left
                        pos |= 16;
                        // back_left_up_c++;
                    } else { // right
                        pos |= 32;
                        // back_right_up_c++;
                    }
                } else { // down
                    if ((tree->s_g[1].x-tree->s_g[0].x)/2+tree->s_g[0].x <= triangle->sommet[i].x
                    && triangle->sommet[i].x <= tree->s_g[1].x) { // left
                        pos |= 64;
                        // back_left_down_c++;
                    } else { // right
                        pos |= 128;
                        // back_right_down_c++;
                    }
                }
            }
        }

        // if (front_left_up_c == 3) {
        //     list_append(&front_left_up, create_link(triangle));
        // } else if (front_left_up_c == 2) {
        //     triangle_t *clipped_triangle = clip_triangle(triangle, tree->s_g);
        //     if (clipped_triangle) {
        //         list_append(&front_left_up, create_link(clipped_triangle));
        //     }
        // }

        /* If the triangle has some points outside of the cube, we clip by the
         * box and add the clipped triangle to the list
         */
        // if (pos != 1 && pos != 2 && pos != 4 && pos != 8 && pos != 16 && pos != 32 && pos != 64 && pos != 128) {
        //     triangle_t *clipped_triangle = clip_triangle(triangle, tree->s_g);
            // int nClippedTriangle = 0;
            // triangle_t Clipped[6] = {0};
            // if ((nClippedTriangle = Triangle_ClipAgainstSG(triangle, tree->s_g, &Clipped)) == -1)
            //     return;

            // for (int i = 0; i < nClippedTriangle; ++i) {
            //     if (Clipped[i].sommet[0].x == 0 && Clipped[i].sommet[0].y == 0 && Clipped[i].sommet[0].z == 0)
            //         continue;
            //     if (pos & 1) list_append(&front_left_up, create_link(&Clipped[i]));
            //     if (pos & 2) list_append(&front_right_up, create_link(&Clipped[i]));
            //     if (pos & 4) list_append(&front_left_down, create_link(&Clipped[i]));
            //     if (pos & 8) list_append(&front_right_down, create_link(&Clipped[i]));
            //     if (pos & 16) list_append(&back_left_up, create_link(&Clipped[i]));
            //     if (pos & 32) list_append(&back_right_up, create_link(&Clipped[i]));
            //     if (pos & 64) list_append(&back_left_down, create_link(&Clipped[i]));
            //     if (pos & 128) list_append(&back_right_down, create_link(&Clipped[i]));
            // }
        //     list_remove(&(mesh), mesh, NULL);
        //     continue;
        // }
        if (pos & 1) list_append(&front_left_up, create_link(triangle));
        if (pos & 2) list_append(&front_right_up, create_link(triangle));
        if (pos & 4) list_append(&front_left_down, create_link(triangle));
        if (pos & 8) list_append(&front_right_down, create_link(triangle));
        if (pos & 16) list_append(&back_left_up, create_link(triangle));
        if (pos & 32) list_append(&back_right_up, create_link(triangle));
        if (pos & 64) list_append(&back_left_down, create_link(triangle));
        if (pos & 128) list_append(&back_right_down, create_link(triangle));

        // if (front_left_up_c == 3) list_append(&front_left_up, create_link(triangle));
        // if (front_left_down_c == 3) list_append(&front_left_down, create_link(triangle));
        // if (front_right_up_c == 3) list_append(&front_right_up, create_link(triangle));
        // if (front_right_down_c == 3) list_append(&front_right_down, create_link(triangle));
        // if (back_left_up_c == 3) list_append(&back_left_up, create_link(triangle));
        // if (back_left_down_c == 3) list_append(&back_left_down, create_link(triangle));
        // if (back_right_up_c == 3) list_append(&back_right_up, create_link(triangle));
        // if (back_right_down_c == 3) list_append(&back_right_down, create_link(triangle));

        list_remove(&(mesh), mesh, NULL);
    }

    unsigned len_front_left_up = len_link(front_left_up);
    unsigned len_front_left_down = len_link(front_left_down);
    unsigned len_front_right_up = len_link(front_right_up);
    unsigned len_front_right_down = len_link(front_right_down);
    unsigned len_back_left_up = len_link(back_left_up);
    unsigned len_back_left_down = len_link(back_left_down);
    unsigned len_back_right_up = len_link(back_right_up);
    unsigned len_back_right_down = len_link(back_right_down);

    // printf("front_left_up : %d\n", len_front_left_up);
    // printf("front_left_down : %d\n", len_front_left_down);
    // printf("front_right_up : %d\n", len_front_right_up);
    // printf("front_right_down : %d\n", len_front_right_down);
    // printf("back_left_up : %d\n", len_back_left_up);
    // printf("back_left_down : %d\n", len_back_left_down);
    // printf("back_right_up : %d\n", len_back_right_up);
    // printf("back_right_down : %d\n", len_back_right_down);

    check_recur(tree, front_left_up, 0, len_front_left_up, len_front_left_up == len);
    check_recur(tree, front_left_down, 1, len_front_left_down, len_front_left_down == len);
    check_recur(tree, front_right_up, 2, len_front_right_up, len_front_right_up == len);
    check_recur(tree, front_right_down, 3, len_front_right_down, len_front_right_down == len);
    check_recur(tree, back_left_up, 4, len_back_left_up, len_back_left_up == len);
    check_recur(tree, back_left_down, 5, len_back_left_down, len_back_left_down == len);
    check_recur(tree, back_right_up, 6, len_back_right_up, len_back_right_up == len);
    check_recur(tree, back_right_down, 7, len_back_right_down, len_back_right_down == len);
    #ifdef DEBUG_MODE
    --deph;
    print_deph(deph);
    #endif
}

#define _powf(x) ((x)*(x))

// static bool is_triangle_in_sphere(sfVector4f center, float radius, triangle_t *triangle)
// {
//     for (unsigned i = 0; i < 3; ++i) {
//         sfVector4f vertex = triangle->sommet[i];
//         float distance_squared = _powf(vertex.x - center.x) + _powf(vertex.y - center.y) + _powf(vertex.z - center.z);
//         if (distance_squared > _powf(radius))
//             return false;
//     }
//     return true;
// }

// static bool is_sphere_triangle_collide(sfVector4f center, float radius, triangle_t *triangle)
// {
//     sfVector4f triangle_normal = Vector_CrossProduct(Vector_Sub(triangle->sommet[1], triangle->sommet[0]), Vector_Sub(triangle->sommet[2], triangle->sommet[0]));
//     triangle_normal = Vector_Div(triangle_normal, Vector_Length(triangle_normal));

//     float signed_distance = Vector_DotProduct(Vector_Sub(center, triangle->sommet[0]), triangle_normal);

//     return ABS(signed_distance) < radius;
// }
// static bool is_sphere_triangle_collide(sfVector4f sphere_center, float sphere_radius, triangle_t triangle) {
//     sfVector4f triangle_normal = Vector_CrossProduct(Vector_Sub(triangle.sommet[1], triangle.sommet[0]), Vector_Sub(triangle.sommet[2], triangle.sommet[0]));
//     triangle_normal = Vector_Normalise(triangle_normal);

//     float signed_distance = Vector_DotProduct(Vector_Sub(sphere_center, triangle.sommet[0]), triangle_normal);

//     return fabs(signed_distance) < sphere_radius;
// }

// def resolve_sphere_triangle_collision(sphere_center, sphere_radius, triangle_vertices):
//     triangle_normal = np.cross(triangle_vertices[1] - triangle_vertices[0], triangle_vertices[2] - triangle_vertices[0])
//     triangle_normal /= np.linalg.norm(triangle_normal)

//     signed_distance = np.dot(sphere_center - triangle_vertices[0], triangle_normal)

//     if abs(signed_distance) < sphere_radius:
//         penetration_depth = sphere_radius - abs(signed_distance)

//         # add if triangle is under the sphere, subtract if triangle is above the sphere
//         if signed_distance < 0:
//             sphere_center -= penetration_depth * triangle_normal
//         else:
//             sphere_center += penetration_depth * triangle_normal

// static void resolve_sphere_triangle_collidion(sfVector4f *center, float radius, triangle_t *triangle)
// {
//     sfVector4f triangle_normal = Vector_CrossProduct(Vector_Sub(triangle->sommet[1], triangle->sommet[0]), Vector_Sub(triangle->sommet[2], triangle->sommet[0])); // it's not the normal, it's the vector of the triangle
//     triangle_normal = Vector_Div(triangle_normal, Vector_Length(triangle_normal));

//     float signed_distance = Vector_DotProduct(Vector_Sub(*center, triangle->sommet[0]), triangle_normal);

//     if (ABS(signed_distance) < radius) {
//         float penetration_depth = radius - ABS(signed_distance);
//         if (signed_distance < 0) {
//             *center = Vector_Sub(*center, Vector_Mul(triangle_normal, penetration_depth));
//         } else {
//             *center = Vector_Add(*center, Vector_Mul(triangle_normal, penetration_depth));
//         }
//     }
// }

// static void resolve_sphere_triangle_collidion(sfVector4f *center, float radius, triangle_t triangle)
// {
//     sfVector4f triangle_normal = Vector_CrossProduct(Vector_Sub(triangle.sommet[1], triangle.sommet[0]), Vector_Sub(triangle.sommet[2], triangle.sommet[0])); // it's not the normal, it's the vector of the triangle
//     triangle_normal = Vector_Div(triangle_normal, Vector_Length(triangle_normal));

//     float signed_distance = Vector_DotProduct(Vector_Sub(*center, triangle.sommet[0]), triangle_normal);

//     if (ABS(signed_distance) < radius) {
//         float penetration_depth = radius - ABS(signed_distance);
//         if (signed_distance < 0) {
//             *center = Vector_Sub(*center, Vector_Mul(triangle_normal, penetration_depth));
//         } else {
//             *center = Vector_Add(*center, Vector_Mul(triangle_normal, penetration_depth));
//         }
//     }
// }


// static bool is_in_triangle(sfVector4f point, triangle_t *triangle)
// {
//     sfVector4f v0 = triangle->sommet[1];
//     sfVector4f v1 = triangle->sommet[2];
//     sfVector4f v2 = triangle->sommet[0];

//     // Subtract the coordinates of the third vertex from the other two vertices to get the vectors of the triangle
//     v0.x -= v2.x;
//     v0.y -= v2.y;
//     v0.z -= v2.z;

//     v1.x -= v2.x;
//     v1.y -= v2.y;
//     v1.z -= v2.z;

//     // Subtract the coordinates of the third vertex from the point to get a vector relative to the triangle
//     sfVector4f relativePoint = point;
//     relativePoint.x -= v2.x;
//     relativePoint.y -= v2.y;
//     relativePoint.z -=v2.z;

//     // Calculate dot products between vectors in order to calculate u and v parameters for barycentric coordinates
//     float dot00 = Vector_DotProduct(v0, v0);
// 	float dot01 = Vector_DotProduct(v0, v1);
// 	float dot02 = Vector_DotProduct(v0, relativePoint);
// 	float dot11 = Vector_DotProduct(v1, v1);
// 	float dot12 = Vector_DotProduct(v1, relativePoint);

//     // Calculate inverse denominator for barycentric coordinates calculation and use it to calculate u and v parameters for barycentric coordinates
//     float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
//     float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
//     float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

//     return (u >= 0) && (v >= 0) && (u + v < 1);
// }

// void csfml_draw_cube(sfVector3f s_g[2])
// {
//     sfVector2f pos = {s_g[0].x, s_g[0].y};
//     sfVector2f size = {s_g[1].x - s_g[0].x, s_g[1].y - s_g[0].y};
//     sfRectangleShape *rect = sfRectangleShape_create();
//     sfRectangleShape_setPosition(rect, pos);
//     sfRectangleShape_setSize(rect, size);
//     sfRectangleShape_setFillColor(rect, sfRed);
//     sfRectangleShape_setOutlineColor(rect, sfRed);
//     sfRectangleShape_setOutlineThickness(rect, 1);
//     sfRenderWindow_drawRectangleShape(engine.window, rect, NULL);
//     sfRectangleShape_destroy(rect);
// }

// static bool is_in_cube(sfVector4f point, sfVector3f s_g[2])
// {
//     return (s_g[0].x <= point.x && s_g[0].y <= point.y && s_g[0].z <= point.z) && (s_g[1].x >= point.x && s_g[1].y >= point.y && s_g[1].z >= point.z);
// }

static bool sphere_in_cube(sfVector4f point, float radius, sfVector3f s_g[2])
{
    return (s_g[0].x <= point.x - radius && s_g[0].y <= point.y - radius && s_g[0].z <= point.z - radius) && (s_g[1].x >= point.x + radius && s_g[1].y >= point.y + radius && s_g[1].z >= point.z + radius);
}

void add_cube_box_as_mesh_in_list(sfVector3f s_g[2])
{
    mesh_t *mesh = calloc(1, sizeof(mesh_t));
    mesh->type = CUBE;

    mesh->lTriangle = NULL;
    // SOUTH
    triangle_t *triangle = calloc(1, sizeof(triangle_t));
    triangle->sommet[0] = (sfVector4f){s_g[0].x, s_g[0].y, s_g[0].z, 1};
    triangle->sommet[1] = (sfVector4f){s_g[0].x, s_g[1].y, s_g[0].z, 1};
    triangle->sommet[2] = (sfVector4f){s_g[1].x, s_g[1].y, s_g[0].z, 1};
    triangle->usemtl = NONE;
    list_append(&(mesh->lTriangle), create_link(triangle));
    triangle = calloc(1, sizeof(triangle_t));
    triangle->sommet[0] = (sfVector4f){s_g[0].x, s_g[0].y, s_g[0].z, 1};
    triangle->sommet[1] = (sfVector4f){s_g[1].x, s_g[1].y, s_g[0].z, 1};
    triangle->sommet[2] = (sfVector4f){s_g[1].x, s_g[0].y, s_g[0].z, 1};
    triangle->usemtl = NONE;
    list_append(&(mesh->lTriangle), create_link(triangle));
    // EAST
    triangle = calloc(1, sizeof(triangle_t));
    triangle->sommet[0] = (sfVector4f){s_g[1].x, s_g[0].y, s_g[0].z, 1};
    triangle->sommet[1] = (sfVector4f){s_g[1].x, s_g[1].y, s_g[0].z, 1};
    triangle->sommet[2] = (sfVector4f){s_g[1].x, s_g[1].y, s_g[1].z, 1};
    triangle->usemtl = NONE;
    list_append(&(mesh->lTriangle), create_link(triangle));
    triangle = calloc(1, sizeof(triangle_t));
    triangle->sommet[0] = (sfVector4f){s_g[1].x, s_g[0].y, s_g[0].z, 1};
    triangle->sommet[1] = (sfVector4f){s_g[1].x, s_g[1].y, s_g[1].z, 1};
    triangle->sommet[2] = (sfVector4f){s_g[1].x, s_g[0].y, s_g[1].z, 1};
    triangle->usemtl = NONE;
    list_append(&(mesh->lTriangle), create_link(triangle));
    // NORTH
    triangle = calloc(1, sizeof(triangle_t));
    triangle->sommet[0] = (sfVector4f){s_g[1].x, s_g[0].y, s_g[1].z, 1};
    triangle->sommet[1] = (sfVector4f){s_g[1].x, s_g[1].y, s_g[1].z, 1};
    triangle->sommet[2] = (sfVector4f){s_g[0].x, s_g[1].y, s_g[1].z, 1};
    triangle->usemtl = NONE;
    list_append(&(mesh->lTriangle), create_link(triangle));
    triangle = calloc(1, sizeof(triangle_t));
    triangle->sommet[0] = (sfVector4f){s_g[1].x, s_g[0].y, s_g[1].z, 1};
    triangle->sommet[1] = (sfVector4f){s_g[0].x, s_g[1].y, s_g[1].z, 1};
    triangle->sommet[2] = (sfVector4f){s_g[0].x, s_g[0].y, s_g[1].z, 1};
    triangle->usemtl = NONE;
    list_append(&(mesh->lTriangle), create_link(triangle));
    // WEST
    triangle = calloc(1, sizeof(triangle_t));
    triangle->sommet[0] = (sfVector4f){s_g[0].x, s_g[0].y, s_g[1].z, 1};
    triangle->sommet[1] = (sfVector4f){s_g[0].x, s_g[1].y, s_g[1].z, 1};
    triangle->sommet[2] = (sfVector4f){s_g[0].x, s_g[1].y, s_g[0].z, 1};
    triangle->usemtl = NONE;
    list_append(&(mesh->lTriangle), create_link(triangle));
    triangle = calloc(1, sizeof(triangle_t));
    triangle->sommet[0] = (sfVector4f){s_g[0].x, s_g[0].y, s_g[1].z, 1};
    triangle->sommet[1] = (sfVector4f){s_g[0].x, s_g[1].y, s_g[0].z, 1};
    triangle->sommet[2] = (sfVector4f){s_g[0].x, s_g[0].y, s_g[0].z, 1};
    triangle->usemtl = NONE;
    list_append(&(mesh->lTriangle), create_link(triangle));
    // TOP
    triangle = calloc(1, sizeof(triangle_t));
    triangle->sommet[0] = (sfVector4f){s_g[0].x, s_g[1].y, s_g[0].z, 1};
    triangle->sommet[1] = (sfVector4f){s_g[0].x, s_g[1].y, s_g[1].z, 1};
    triangle->sommet[2] = (sfVector4f){s_g[1].x, s_g[1].y, s_g[1].z, 1};
    triangle->usemtl = NONE;
    list_append(&(mesh->lTriangle), create_link(triangle));
    triangle = calloc(1, sizeof(triangle_t));
    triangle->sommet[0] = (sfVector4f){s_g[0].x, s_g[1].y, s_g[0].z, 1};
    triangle->sommet[1] = (sfVector4f){s_g[1].x, s_g[1].y, s_g[1].z, 1};
    triangle->sommet[2] = (sfVector4f){s_g[1].x, s_g[1].y, s_g[0].z, 1};
    triangle->usemtl = NONE;
    list_append(&(mesh->lTriangle), create_link(triangle));
    // BOTTOM
    triangle = calloc(1, sizeof(triangle_t));
    triangle->sommet[0] = (sfVector4f){s_g[1].x, s_g[0].y, s_g[1].z, 1};
    triangle->sommet[1] = (sfVector4f){s_g[0].x, s_g[0].y, s_g[1].z, 1};
    triangle->sommet[2] = (sfVector4f){s_g[0].x, s_g[0].y, s_g[0].z, 1};
    triangle->usemtl = NONE;
    list_append(&(mesh->lTriangle), create_link(triangle));
    triangle = calloc(1, sizeof(triangle_t));
    triangle->sommet[0] = (sfVector4f){s_g[1].x, s_g[0].y, s_g[1].z, 1};
    triangle->sommet[1] = (sfVector4f){s_g[0].x, s_g[0].y, s_g[0].z, 1};
    triangle->sommet[2] = (sfVector4f){s_g[1].x, s_g[0].y, s_g[0].z, 1};
    triangle->usemtl = NONE;
    list_append(&(mesh->lTriangle), create_link(triangle));

    list_append(&(LIST_OBJS), create_link(mesh));
}

// static bool is_sphere_triangle_collision(sfVector4f sphere_center, float sphere_radius, triangle_t triangle) {
//     sfVector4f triangle_normal = Vector_CrossProduct(Vector_Sub(triangle.sommet[1], triangle.sommet[0]), Vector_Sub(triangle.sommet[2], triangle.sommet[0]));
//     triangle_normal = Vector_Normalise(triangle_normal);

//     float signed_distance = Vector_DotProduct(Vector_Sub(sphere_center, triangle.sommet[0]), triangle_normal);
//     if (fabs(signed_distance) > sphere_radius)
//         return false;

//     for (int i = 0; i < 3; i++) {
//         sfVector4f edge_start = triangle.sommet[i];
//         sfVector4f edge_end = triangle.sommet[(i + 1) % 3];

//         sfVector4f edge_direction = Vector_Sub(edge_end, edge_start);
//         float edge_projection = Vector_DotProduct(Vector_Sub(sphere_center, edge_start), edge_direction) / Vector_DotProduct(edge_direction, edge_direction);
//         sfVector4f closest_point_on_edge = Vector_Add(edge_start, Vector_Mul(edge_direction, edge_projection));

//         if (0 <= edge_projection && edge_projection <= 1 && Vector_Length(Vector_Sub(closest_point_on_edge, sphere_center)) < sphere_radius)
//             return true;
//     }
//     return false;
// }

// static sfVector4f resolve_sphere_triangle_collision(sfVector4f sphere_center, float sphere_radius, triangle_t triangle) {
//     sfVector4f triangle_normal = Vector_CrossProduct(Vector_Sub(triangle.sommet[1], triangle.sommet[0]), Vector_Sub(triangle.sommet[2], triangle.sommet[0]));
//     triangle_normal = Vector_Normalise(triangle_normal);

//     float signed_distance = Vector_DotProduct(Vector_Sub(sphere_center, triangle.sommet[0]), triangle_normal);

//     if (fabs(signed_distance) < sphere_radius) {
//         float penetration_depth = sphere_radius - fabs(signed_distance);

//         sfVector4f penetration_vector = Vector_Mul(triangle_normal, penetration_depth);

//         if (signed_distance < 0) {
//             return Vector_Sub(sphere_center, penetration_vector);
//         } else {
//             return Vector_Add(sphere_center, penetration_vector);
//         }
//     }
//     return sphere_center;
// }

void get_bvh(Tree_t *tree, sfVector4f *point, float radius)
{
    // ++deph;
    // print_deph(deph);
    if (tree->triangle) {
        // for (unsigned i = 0; tree->triangle[i]; ++i) {
        //     if (is_sphere_triangle_collision(*point, radius, *(tree->triangle)[i])) {
        //         // printf("bf point: %f, %f, %f  |  \n", point->x, point->y, point->z);
        //         // *point = resolve_sphere_triangle_collision(*point, radius, *(tree->triangle)[i]);
        //         #ifdef DEBUG_MODE
        //         printf("point(%d): %f, %f, %f\n", i, point->x, point->y, point->z);
        //         #endif
        //         // printf("af point: %f, %f, %f\n", point->x, point->y, point->z);
        //     }
        // }
        // #ifdef DEBUG_MODE
        add_cube_box_as_mesh_in_list(tree->s_g);
        // #endif
        // engine.state = IDLE;
        // engine.velocity_y = 5.f;
    } else {
        for (unsigned i = 0; i < 8; ++i) {
            if (tree->node[i]) {
                if (sphere_in_cube(*point, radius, tree->node[i]->s_g)) {
                    // printf("smaller cube: %f, %f, %f  |  \n", tree->node[i]->s_g[0].x, tree->node[i]->s_g[0].y, tree->node[i]->s_g[0].z);
                    // printf("bf point: %f, %f, %f  |  \n", point->x, point->y, point->z);
                    // printf("greater cube: %f, %f, %f\n", tree->node[i]->s_g[1].x, tree->node[i]->s_g[1].y, tree->node[i]->s_g[1].z);
                    // csfml_draw_cube(tree->node[i]->s_g);
                    get_bvh(tree->node[i], point, radius);
                    // --deph;
                    return;
                }
            }
        }
    }
    // --deph;
}

void clean_cube_box_from_list(void)
{
    link_t *tmp = LIST_OBJS;
    if (!LIST_OBJS)
        return;
    do {
        if (((mesh_t *) tmp->obj)->type == CUBE) {
            clean_triangles((link_t *)((mesh_t *) tmp->obj)->lTriangle);
            free((mesh_t *) tmp->obj);
            list_remove(&(LIST_OBJS), tmp, NULL);
            tmp = LIST_OBJS;
        } else {
            tmp = tmp->next;
        }
    } while (tmp && tmp != engine.list_objs);
}

void clean_bvh(Tree_t *tree)
{
    if (tree->triangle) {
        free(tree->triangle);
    } else {
        for (unsigned i = 0; i < 8; ++i) {
            if (tree->node[i]) {
                clean_bvh(tree->node[i]);
                free(tree->node[i]);
            }
        }
    }
}

// sfVector3f get_bvh(Tree_t *tree, sfVector4f point)
// {
//     sfVector3f connect_point = {0, 0, 0};
//     if (tree->triangle) {
//         print_triangle(tree->triangle);
//         print_vector(point);
//         if (is_in_triangle(point, tree->triangle)) {
//             connect_point = average_triangle(tree->triangle);
//             printf("    connect_point : %f %f %f\n", connect_point.x, connect_point.y, connect_point.z);
//         }
//     } else {
//         printf("    pos : \n");
//         print_vector(point);
//         printf("    left : \n");
//         print_cube(tree->node[0]->s_g);
//         printf("    right : \n");
//         print_cube(tree->node[2]->s_g);
//         if (is_in_cube(point, tree->node[0]->s_g)) {
//             printf("    left -> \n");
//             connect_point = get_bvh(tree->node[0], point);
//         } else if (is_in_cube(point, tree->node[2]->s_g)) {
//             printf("    right -> \n");
//             connect_point = get_bvh(tree->node[2], point);
//         }
//     }
//     return connect_point;
// }

// void print_bvh(Tree_t *tree)
// {
//     if (tree->triangle) {
//         printf("triangle: %f %f %f\n", tree->triangle->sommet[0].x, tree->triangle->sommet[0].y, tree->triangle->sommet[0].z);
//     } else {
//         if (tree->node[0]) {
//             print_bvh(tree->node[0]);
//         }
//         if (tree->node[2]) {
//             print_bvh(tree->node[2]);
//         }
//     }
// }
