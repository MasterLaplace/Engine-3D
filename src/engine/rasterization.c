/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** rasterization
*/

#include "engine.h"


//* Model to World (M2W) */

inline static void Matrix_MakeRotateX(float (*matrix)[4], float angle)
{
    float rot_matrix[4][4] = {
        { 1, 0, 0, 0 },
        { 0, cosf(angle), -sinf(angle), 0 },
        { 0, sinf(angle), cosf(angle), 0 },
        { 0, 0, 0, 1 }
    };

    memcpy(*matrix, rot_matrix, sizeof(rot_matrix));
}

inline static void Matrix_MakeRotateY(float (*matrix)[4], float angle)
{
    float rot_matrix[4][4] = {
        { cosf(angle), 0, sinf(angle), 0 },
        { 0, 1, 0, 0 },
        { -sinf(angle), 0, cosf(angle), 0 },
        { 0, 0, 0, 1 }
    };

    memcpy(*matrix, rot_matrix, sizeof(rot_matrix));
}

inline static void Matrix_MakeRotateZ(float (*matrix)[4], float angle)
{
    float rot_matrix[4][4] = {
        { cosf(angle), -sinf(angle), 0, 0 },
        { sinf(angle), cosf(angle), 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    };

    memcpy(*matrix, rot_matrix, sizeof(rot_matrix));
}

inline static void Matrix_MakeTranslate(float (*matrix)[4], float x, float y, float z)
{
    float tran_matrix[4][4] = {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { x, y, z, 1 }
    };

    memcpy(*matrix, tran_matrix, sizeof(tran_matrix));
}

inline static void Matrix_MakeScale(float (*matrix)[4], float x, float y, float z)
{
    float sca_matrix[4][4] = {
        { x, 0, 0, 0 },
        { 0, y, 0, 0 },
        { 0, 0, z, 0 },
        { 0, 0, 0, 1 }
    };

    memcpy(*matrix, sca_matrix, sizeof(sca_matrix));
}


//* World to View (W2V) */

sfVector4f get_surface_normal(triangle_t triangle)
{
    sfVector4f vector1, vector2;

    vector1 = Vector_Sub(triangle.sommet[1], triangle.sommet[0]);
    vector2 = Vector_Sub(triangle.sommet[2], triangle.sommet[0]);

    return Vector_Normalise(Vector_CrossProduct(vector1, vector2));
}

void Matrix_View(sfVector4f pos, sfVector4f dir, sfVector4f up)
{
    sfVector4f newForward = Vector_Normalise(Vector_Sub(dir, pos));
    sfVector4f a = Vector_Mul(newForward, Vector_DotProduct(up, newForward));
    sfVector4f newUp = Vector_Normalise(Vector_Sub(up, a));
    sfVector4f newRight = Vector_CrossProduct(newUp, newForward);

    float view_matrix[4][4] = {
        { newRight.x, newRight.y, newRight.z, 0 },
        { newUp.x, newUp.y, newUp.z, 0 },
        { newForward.x, newForward.y, newForward.z, 0 },
        { pos.x, pos.y, pos.z, 1 }
    };

    matrix matrix = Matrix_QuickInverse(view_matrix);
    memcpy(engine.WorldtoView, matrix.m, sizeof(view_matrix));
}


//* View to Projection (V2P) */

inline void Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar)
{
    float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * PI);

    float proj_matrix[4][4] = {
        { fAspectRatio * fFovRad, 0, 0, 0 },
        { 0, fFovRad, 0, 0 },
        { 0, 0, fFar / (fFar - fNear), 1 },
        { 0, 0, (-fFar * fNear) / (fFar - fNear), 0 }
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

    triangle->sommet[0].x *= -1.0f;
    triangle->sommet[0].y *= -1.0f;
    triangle->sommet[1].x *= -1.0f;
    triangle->sommet[1].y *= -1.0f;
    triangle->sommet[2].x *= -1.0f;
    triangle->sommet[2].y *= -1.0f;

    // Scale
    triangle->sommet[0] = Vector_Add(triangle->sommet[0], (sfVector4f){1.f, 1.f, 0.f, 1.f});
    triangle->sommet[1] = Vector_Add(triangle->sommet[1], (sfVector4f){1.f, 1.f, 0.f, 1.f});
    triangle->sommet[2] = Vector_Add(triangle->sommet[2], (sfVector4f){1.f, 1.f, 0.f, 1.f});

    triangle->sommet[0].x *= 0.5f * (float) WIN_X;
    triangle->sommet[0].y *= 0.5f * (float) WIN_Y;
    triangle->sommet[1].x *= 0.5f * (float) WIN_X;
    triangle->sommet[1].y *= 0.5f * (float) WIN_Y;
    triangle->sommet[2].x *= 0.5f * (float) WIN_X;
    triangle->sommet[2].y *= 0.5f * (float) WIN_Y;
}

//* Calculation of 2D coordinates */

void vectors_3d_to_2d(bool drunkerMode)
{
    // World to View (W2V)
    float Rotate[4][4];
    float RotateY[4][4];
    float RotateX[4][4];
    sfVector4f Dir = {0, 0, 1, 1};
    sfVector4f Up = {0, 1, 0, 1};

    if (drunkerMode) {
        Matrix_MakeRotateX(RotateX, engine.t);
        Matrix_MakeRotateY(RotateY, engine.t);
        Matrix_Multiply(Rotate, RotateY, RotateX);
    } else {
        Matrix_MakeRotateX(RotateX, engine.fawX);
        Matrix_MakeRotateY(RotateY, engine.fawY);
        Matrix_Multiply(Rotate, RotateX, RotateY);
    }
    engine.Dir = Matrix_MultiplyVector(engine.Dir, Rotate, Dir);
    Dir = Vector_Add(engine.Pos, engine.Dir);
    Matrix_View(engine.Pos, Dir, Up);
}

//* Mesh transformation */

void Mesh_Transform(sfVector4f pos, sfVector3f angle, sfVector3f scale)
{
    // Model to World (M2W)
    float Rotate[4][4];
    float RotateY[4][4];
    float RotateX[4][4];
    float RotateZ[4][4];
    float Translate[4][4];
    float Scale[4][4];

    // Rotation matrices : around the z-axis - around the y-axis - around the x-axis
    Matrix_MakeRotateX(RotateX, angle.x);
    Matrix_MakeRotateY(RotateY, angle.y);
    Matrix_MakeRotateZ(RotateZ, angle.z);
    Matrix_Multiply(Rotate, RotateX, RotateY);
    Matrix_Multiply(Rotate, Rotate, RotateZ);

    // Translation matrix
    Matrix_MakeTranslate(Translate, pos.x, pos.y, pos.z);
    Matrix_Multiply(engine.ModeltoWorld, Rotate, Translate);
    // Scaling matrix
    Matrix_MakeScale(Scale, scale.x, scale.y, scale.z);
    Matrix_Multiply(engine.ModeltoWorld, engine.ModeltoWorld, Scale);
}
