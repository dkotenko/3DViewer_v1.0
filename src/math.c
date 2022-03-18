#include "scop.h"
#include <math.h>

void InitRotationX(matrix_t *m, float x)
{
    float **m = ScaleTrans.matrix;
    
    m[0][0] = 1.0f; m[0][1] = 0.0f   ; m[0][2] = 0.0f    ; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = cosf(x); m[1][2] = -sinf(x); m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = sinf(x); m[2][2] = cosf(x) ; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f   ; m[3][2] = 0.0f    ; m[3][3] = 1.0f;
}


void InitRotationY(matrix_t matrix, float y)
{
    float **m = ScaleTrans.matrix;

    m[0][0] = cosf(y); m[0][1] = 0.0f; m[0][2] = -sinf(y); m[0][3] = 0.0f;
    m[1][0] = 0.0f   ; m[1][1] = 1.0f; m[1][2] = 0.0f    ; m[1][3] = 0.0f;
    m[2][0] = sinf(y); m[2][1] = 0.0f; m[2][2] = cosf(y) ; m[2][3] = 0.0f;
    m[3][0] = 0.0f   ; m[3][1] = 0.0f; m[3][2] = 0.0f    ; m[3][3] = 1.0f;
}


void InitRotationZ(matrix_t matrix, float z)
{
    float **m = ScaleTrans.matrix;

    m[0][0] = cosf(z); m[0][1] = -sinf(z); m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = sinf(z); m[1][1] = cosf(z) ; m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f   ; m[2][1] = 0.0f    ; m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f   ; m[3][1] = 0.0f    ; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void InitScaleTransform(matrix_t matrix, float ScaleX, float ScaleY, float ScaleZ)
{
    float **m = ScaleTrans.matrix;

    m[0][0] = ScaleX; m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
    m[1][0] = 0.0f;   m[1][1] = ScaleY; m[1][2] = 0.0f;   m[1][3] = 0.0f;
    m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = ScaleZ; m[2][3] = 0.0f;
    m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;
}

void InitRotateTransform(matrix_t *m, float RotateX, float RotateY, float RotateZ)
{
    matrix_t rx, ry, rz;

    float x = ToRadian(RotateX);
    float y = ToRadian(RotateY);
    float z = ToRadian(RotateZ);

    matrix_t rx = s21_matrix_create(4, 4);
    matrix_t ry = s21_matrix_create(4, 4);
    matrix_t rz = s21_matrix_create(4, 4);
    rx.InitRotationX(rx.matrix, x);
    ry.InitRotationY(ry.matrix, y);
    rz.InitRotationZ(rz.matrix, z);

    *m = s21_mult_matrix(rz, ry);
    *m = s21_mult_matrix(m, rx);
}


void InitTranslationTransform(matrix_t *matrix, float x, float y, float z)
{
    float **m = matrix.m;

    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void InitOrthoProjTransform(const OrthoProjInfo& p)
{
    float l = p.l;
    float r = p.r;
    float b = p.b;
    float t = p.t;
    float n = p.n;
    float f = p.f;

    m[0][0] = 2.0f/(r - l); m[0][1] = 0.0f;         m[0][2] = 0.0f;         m[0][3] = -(r + l)/(r - l);
    m[1][0] = 0.0f;         m[1][1] = 2.0f/(t - b); m[1][2] = 0.0f;         m[1][3] = -(t + b)/(t - b);
    m[2][0] = 0.0f;         m[2][1] = 0.0f;         m[2][2] = 2.0f/(f - n); m[2][3] = -(f + n)/(f - n);
    m[3][0] = 0.0f;         m[3][1] = 0.0f;         m[3][2] = 0.0f;         m[3][3] = 1.0;
}

void InitTranslationTransform(t_matrix CameraTranslationTrans, float x, float y, float z)
{
    float **m = CameraTranslationTrans.matrix;

    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void InitTranslationTransform_vec3d(t_matrix CameraTranslationTrans, const t_vec3f Pos)
{
    InitTranslationTransform(CameraTranslationTrans, Pos.x, Pos.y, Pos.z);
}

void InitCameraTransform(const t_vec3f Target, const t_vec3f Up)
{
    Vector3f N = Normalize(Target);
    Vector3f U = Cross(Up, N);
    U = Normalize(U);

    Vector3f V = Cross(N, U);

    m[0][0] = U.x;   m[0][1] = U.y;   m[0][2] = U.z;   m[0][3] = 0.0f;
    m[1][0] = V.x;   m[1][1] = V.y;   m[1][2] = V.z;   m[1][3] = 0.0f;
    m[2][0] = N.x;   m[2][1] = N.y;   m[2][2] = N.z;   m[2][3] = 0.0f;
    m[3][0] = 0.0f;  m[3][1] = 0.0f;  m[3][2] = 0.0f;  m[3][3] = 1.0f;
}


void InitCameraTransform(matrix_t *CameraRotateTrans, t_vec3f Pos, t_vec3f Target, t_vec3f Up)
{
    Matrix4f CameraTranslation = s21_matrix_create(4, 4);
    InitTranslationTransform(CameraTranslation, -Pos.x, -Pos.y, -Pos.z);

    Matrix4f CameraRotateTrans = s21_matrix_create(4, 4);
    InitCameraTransform(CameraRotateTrans, Target, Up);

    *CameraRotateTrans = s21_mult_matrix(CameraRotateTrans, CameraTranslation);
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

    if (length == 0) {
        return v;
    }

    norm.x = v.x / Length;
    norm.y /= v.y / Length;
    norm.z /= v.z / Length;

    return norm;
}
