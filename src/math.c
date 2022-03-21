#include "scop.h"
#include <math.h>
#include "s21_matrix.h"
#include "vector.h"

#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

void InitRotationX(matrix_t *ScaleTrans, float x)
{
    float **m = (float **)ScaleTrans->matrix;
    
    m[0][0] = 1.0f; m[0][1] = 0.0f   ; m[0][2] = 0.0f    ; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = cosf(x); m[1][2] = -sinf(x); m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = sinf(x); m[2][2] = cosf(x) ; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f   ; m[3][2] = 0.0f    ; m[3][3] = 1.0f;
}


void InitRotationY(matrix_t ScaleTrans, float y)
{
    float **m = (float **)ScaleTrans.matrix;

    m[0][0] = cosf(y); m[0][1] = 0.0f; m[0][2] = -sinf(y); m[0][3] = 0.0f;
    m[1][0] = 0.0f   ; m[1][1] = 1.0f; m[1][2] = 0.0f    ; m[1][3] = 0.0f;
    m[2][0] = sinf(y); m[2][1] = 0.0f; m[2][2] = cosf(y) ; m[2][3] = 0.0f;
    m[3][0] = 0.0f   ; m[3][1] = 0.0f; m[3][2] = 0.0f    ; m[3][3] = 1.0f;
}


void InitRotationZ(matrix_t ScaleTrans, float z)
{
    float **m = (float **)ScaleTrans.matrix;

    m[0][0] = cosf(z); m[0][1] = -sinf(z); m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = sinf(z); m[1][1] = cosf(z) ; m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f   ; m[2][1] = 0.0f    ; m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f   ; m[3][1] = 0.0f    ; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void InitScaleTransform(matrix_t ScaleTrans, float ScaleX, float ScaleY, float ScaleZ)
{
    float **m = (float **)ScaleTrans.matrix;

    m[0][0] = ScaleX; m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
    m[1][0] = 0.0f;   m[1][1] = ScaleY; m[1][2] = 0.0f;   m[1][3] = 0.0f;
    m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = ScaleZ; m[2][3] = 0.0f;
    m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;
}

void InitRotateTransform(matrix_t *m, float RotateX, float RotateY, float RotateZ)
{
    float x = ToRadian(RotateX);
    float y = ToRadian(RotateY);
    float z = ToRadian(RotateZ);

    matrix_t rx = s21_create_matrix(4, 4);
    matrix_t ry = s21_create_matrix(4, 4);
    matrix_t rz = s21_create_matrix(4, 4);
    InitRotationX(&rx, x);
    InitRotationY(ry, y);
    InitRotationZ(rz, z);

    *m = s21_mult_matrix(&rz, &ry);
    *m = s21_mult_matrix(m, &rx);
}

void InitOrthoProjTransform(matrix_t matrix, OrthoProjInfo p)
{
    float l = p.l;
    float r = p.r;
    float b = p.b;
    float t = p.t;
    float n = p.n;
    float f = p.f;

    float **m = (float **)matrix.matrix;

    m[0][0] = 2.0f/(r - l); m[0][1] = 0.0f;         m[0][2] = 0.0f;         m[0][3] = -(r + l)/(r - l);
    m[1][0] = 0.0f;         m[1][1] = 2.0f/(t - b); m[1][2] = 0.0f;         m[1][3] = -(t + b)/(t - b);
    m[2][0] = 0.0f;         m[2][1] = 0.0f;         m[2][2] = 2.0f/(f - n); m[2][3] = -(f + n)/(f - n);
    m[3][0] = 0.0f;         m[3][1] = 0.0f;         m[3][2] = 0.0f;         m[3][3] = 1.0;
}
#include <stdio.h>

void InitPersProjTransform(matrix_t ProjTransformation, PersProjInfo p)
{
    float **m = (float **)ProjTransformation.matrix;
    const float ar         = p.Width / p.Height;
    const float zRange     = p.zNear - p.zFar;
    const float tanHalfFOV = tanf(ToRadian(p.FOV / 2.0f));

    m[0][0] = 1.0f/(tanHalfFOV * ar); m[0][1] = 0.0f;            m[0][2] = 0.0f;                        m[0][3] = 0.0;
    m[1][0] = 0.0f;                   m[1][1] = 1.0f/tanHalfFOV; m[1][2] = 0.0f;                        m[1][3] = 0.0;
    m[2][0] = 0.0f;                   m[2][1] = 0.0f;            m[2][2] = (-p.zNear - p.zFar)/zRange ; m[2][3] = 2.0f*p.zFar*p.zNear/zRange;
    m[3][0] = 0.0f;                   m[3][1] = 0.0f;            m[3][2] = 1.0f;                        m[3][3] = 0.0;
}

void InitTranslationTransform(matrix_t *matrix, float x, float y, float z)
{
    float **m = (float **)matrix->matrix;

    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void InitTranslationTransform_vec3d(matrix_t CameraTranslationTrans, const t_vec3f Pos)
{
    InitTranslationTransform(&CameraTranslationTrans, Pos.x, Pos.y, Pos.z);
}

void InitCameraTransform_2v(matrix_t *CameraRotateTrans, const t_vec3f Target, const t_vec3f Up)
{
    t_vec3f N = Normalize(Target);
    t_vec3f U = Cross(Up, N);
    U = Normalize(U);
    float **m = (float **)CameraRotateTrans->matrix;

    t_vec3f V = Cross(N, U);

    m[0][0] = U.x;   m[0][1] = U.y;   m[0][2] = U.z;   m[0][3] = 0.0f;
    m[1][0] = V.x;   m[1][1] = V.y;   m[1][2] = V.z;   m[1][3] = 0.0f;
    m[2][0] = N.x;   m[2][1] = N.y;   m[2][2] = N.z;   m[2][3] = 0.0f;
    m[3][0] = 0.0f;  m[3][1] = 0.0f;  m[3][2] = 0.0f;  m[3][3] = 1.0f;
}


void InitCameraTransform_3v(matrix_t *matrix, t_vec3f Pos, t_vec3f Target, t_vec3f Up)
{
    matrix_t CameraTranslation, CameraRotateTrans;
    CameraRotateTrans = s21_create_matrix(4, 4);
    InitTranslationTransform(&CameraTranslation, -Pos.x, -Pos.y, -Pos.z);

    CameraRotateTrans = s21_create_matrix(4, 4);
    InitCameraTransform_2v(&CameraRotateTrans, Target, Up);

    matrix_t mult = s21_mult_matrix(&CameraRotateTrans, &CameraTranslation);
    //s21_free_matrix_array(matrix->matrix, 4);
    matrix->matrix = mult.matrix;
}

t_vec3f Cross(t_vec3f vector, t_vec3f v)
{
    t_vec3f res;

    res.x = vector.y * v.z - vector.z * v.y;
    res.y = vector.z * v.x - vector.x * v.z;
    res.z = vector.x * v.y - vector.y * v.x;

    return res;
}

t_vec3f Normalize(t_vec3f v)
{
    t_vec3f norm;
    const float Length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

    if (Length == 0) {
        return v;
    }

    norm.x = v.x / Length;
    norm.y /= v.y / Length;
    norm.z /= v.z / Length;

    return norm;
}
