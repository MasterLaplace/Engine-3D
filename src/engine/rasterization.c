/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** rasterization
*/

#include "engine.h"

//* Model to World (M2W) */

void Matrix_Multiply(float (*m)[4], float (*m1)[4], float (*m2)[4])
{
    for(sizint i = 0; i < 4; i++) {
        for (sizint j = 0; j < 4; j++) {
            m[j][i] = m1[j][0] * m2[0][i] + m1[j][1] * m2[1][i] + m1[j][2] * m2[2][i] + m1[j][3] * m2[3][i];
        }
    }
}

void Matrix_MakeRotateZYX(float (*matrix)[4], float angleZ, float angleY, float angleX) {
    float cz = cosf(RADIAN(angleZ));
    float sz = sinf(RADIAN(angleZ));
    float cy = cosf(RADIAN(angleY));
    float sy = sinf(RADIAN(angleY));
    float cx = cosf(RADIAN(angleX));
    float sx = sinf(RADIAN(angleX));
    

    float rot_matrix[4][4] = {
        { cz * cy, -sz, sy, 0 },
        { sz, cz * cx, -sx, 0 },
        { -sy, sx, cy * cx, 0 },
        { 0, 0, 0, 1 }
    };

    memcpy(*matrix, rot_matrix, sizeof(rot_matrix));
}

void Matrix_MakeTranslate(float (*matrix)[4], float z, float y, float x) {
    float tran_matrix[4][4] = {
        { 1, 0, 0, x },
        { 0, 1, 0, y },
        { 0, 0, 1, z },
        { 0, 0, 0, 1 }
    };

    memcpy(*matrix, tran_matrix, sizeof(tran_matrix));
}

void Matrix_MakeScale(float (*matrix)[4], float z, float y, float x) {
    float sca_matrix[4][4] = {
        { x, 0, 0, 0 },
        { 0, y, 0, 0 },
        { 0, 0, z, 0 },
        { 0, 0, 0, 1 }
    };

    memcpy(*matrix, sca_matrix, sizeof(sca_matrix));
}


//* World to View (W2V) */

sfVector4f_t Vector_Add(sfVector4f_t v, sfVector4f_t w)
{
    return (sfVector4f_t){v.x + w.x, v.y + w.y, v.z + w.z, 1.f};
}

sfVector4f_t Vector_Sub(sfVector4f_t v, sfVector4f_t w)
{
    return (sfVector4f_t){v.x - w.x, v.y - w.y, v.z - w.z, 1.f};
}

sfVector4f_t Vector_Mul(sfVector4f_t v, float w)
{
    return (sfVector4f_t){v.x * w, v.y * w, v.z * w, w};
}

sfVector4f_t Vector_Div(sfVector4f_t v, float w)
{
    return (sfVector4f_t){v.x / w, v.y / w, v.z / w, w};
}

float Vector_DotProduct(sfVector4f_t v, sfVector4f_t w)
{
    return v.x * w.x + v.y * w.y + v.z * w.z;
}

float Vector_Length(sfVector4f_t v)
{
    return sqrtf(Vector_DotProduct(v, v));
}

sfVector4f_t Vector_Normalise(sfVector4f_t v)
{
    float l = Vector_Length(v);
    return (sfVector4f_t){v.x / l, v.y / l, v.z / l, 1.f};
}

sfVector4f_t Vector_CrossProduct(sfVector4f_t a, sfVector4f_t b)
{
    sfVector4f_t l;

    l.x = a.y * b.z - a.z * b.y;
    l.y = a.z * b.x - a.x * b.z;
    l.z = a.x * b.y - a.y * b.x;
    return l;
}

sfVector4f_t Matrix_MultiplyVector(sfVector4f_t v, float (*m)[4], sfVector4f_t w)
{
    v.x = w.x * m[0][0] + w.y * m[1][0] + w.z * m[2][0] + w.w * m[3][0];
    v.y = w.x * m[0][1] + w.y * m[1][1] + w.z * m[2][1] + w.w * m[3][1];
    v.z = w.x * m[0][2] + w.y * m[1][2] + w.z * m[2][2] + w.w * m[3][2];
    v.w = w.x * m[0][3] + w.y * m[1][3] + w.z * m[2][3] + w.w * m[3][3];
    return v;
}

sfVector4f_t get_surface_normal(triangle_t triangle)
{
    sfVector4f_t vector1, vector2;

    vector1 = Vector_Sub(triangle.sommet[1], triangle.sommet[0]);
    vector2 = Vector_Sub(triangle.sommet[2], triangle.sommet[0]);

    return Vector_Normalise(Vector_CrossProduct(vector1, vector2));
}

void Matrix_View(sfVector4f_t pos, sfVector4f_t dir, sfVector4f_t up)
{
    sfVector4f_t Forward = Vector_Normalise(Vector_Sub(pos, dir));
    sfVector4f_t Sright = Vector_Normalise(Vector_CrossProduct(Forward, up));
    sfVector4f_t Upv = Vector_Normalise(Vector_CrossProduct(Sright, Forward));

    float view_matrix[4][4] = {
        { Sright.x, Sright.y, Sright.z, -pos.x },
        { Upv.x, Upv.y, Upv.z, -pos.y },
        { -Forward.x, -Forward.y, -Forward.z, -pos.z },
        { 0, 0, 0, 1 }
    };

    memcpy(engine.WorldtoView, view_matrix, sizeof(view_matrix));
}

//* View to Projection (V2P) */

void Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar)
{
    float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * PI);

    float proj_matrix[4][4] = {
        { fAspectRatio * fFovRad, 0, 0, 0 },
        { 0, fFovRad, 0, 0 },
        { 0, 0, fFar / (fFar - fNear), 1 },
        { 0, 0, (-fFar * fNear) / (fFar - fNear), 1 }
    };

    memcpy(engine.ViewtoProjection, proj_matrix, sizeof(proj_matrix));
}

//* Scale to Screen (S2S) */

void Scale_in_Screen(triangle_t *triangle)
{
    // Inverse
    triangle->sommet[0] = Vector_Div(triangle->sommet[0], triangle->sommet[0].w);
    triangle->sommet[1] = Vector_Div(triangle->sommet[1], triangle->sommet[1].w);
    triangle->sommet[2] = Vector_Div(triangle->sommet[2], triangle->sommet[2].w);

    // Scale
    triangle->sommet[0] = Vector_Add(triangle->sommet[0], (sfVector4f_t){1.f, 1.f, 0.f, 1.f});
    triangle->sommet[1] = Vector_Add(triangle->sommet[1], (sfVector4f_t){1.f, 1.f, 0.f, 1.f});
    triangle->sommet[2] = Vector_Add(triangle->sommet[2], (sfVector4f_t){1.f, 1.f, 0.f, 1.f});

    triangle->sommet[0].x *= 0.5f * (float) WIN_X;
    triangle->sommet[0].y *= 0.5f * (float) WIN_Y;
    triangle->sommet[1].x *= 0.5f * (float) WIN_X;
    triangle->sommet[1].y *= 0.5f * (float) WIN_Y;
    triangle->sommet[2].x *= 0.5f * (float) WIN_X;
    triangle->sommet[2].y *= 0.5f * (float) WIN_Y;
}

//* Calculation of 2D coordinates */

void vectors_3d_to_2d()
{
    // Model to World (M2W)
    float Rotate[4][4];
    float Translate[4][4];
    float Scale[4][4];

    // Rotation matrices : around the z-axis - around the y-axis - around the x-axis
    Matrix_MakeRotateZYX(Rotate, engine.fawZ, engine.fawY, engine.fawX);
    // Translation matrix
    Matrix_MakeTranslate(Translate, 0.f, 0.f, 0.f);
    Matrix_Multiply(engine.ModeltoWorld, Rotate, Translate);
    // Scaling matrix
    Matrix_MakeScale(Scale, 0.5f, 0.5f, 0.5f);
    Matrix_Multiply(engine.ModeltoWorld, engine.ModeltoWorld, Scale);

    // World to View (W2V)
    sfVector4f_t Dir = {0, 0, 1, 1};
    sfVector4f_t Up = {0, 1, 0, 1};

    engine.Dir = Matrix_MultiplyVector(engine.Dir, engine.ModeltoWorld, Dir);
    Dir = Vector_Add(engine.Pos, engine.Dir);
    Matrix_View(engine.Pos, Dir, Up);
}

sfVertexArray *create_triangle(sfVector2f pt1, sfVector2f pt2, sfVector2f pt3)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVertex vertex1, vertex2, vertex3;

    vertex1 = (sfVertex){.position = pt1, .color = sfWhite};
    vertex2 = (sfVertex){.position = pt2, .color = sfWhite};
    vertex3 = (sfVertex){.position = pt3, .color = sfWhite};

    sfVertexArray_append(vertex_array, vertex1);
    sfVertexArray_append(vertex_array, vertex2);
    sfVertexArray_append(vertex_array, vertex3);
    sfVertexArray_setPrimitiveType(vertex_array, sfTriangleFan);
    return vertex_array;
}
