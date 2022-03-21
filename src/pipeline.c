#include "scop.h"
#include "s21_matrix.h"

t_pipeline t_pipeline_new()
{
    t_pipeline *p = (t_pipeline *)calloc(1, sizeof(t_pipeline));
    if (p) {
        p->m_scale = t_vec3f(1.0f, 1.0f, 1.0f);
        p->m_worldPos = t_vec3f(0.0f, 0.0f, 0.0f);
        p->m_rotateInfo = t_vec3f(0.0f, 0.0f, 0.0f);
    }
    return p;
}

void set_scale_3f(t_pipeline *p, float x, float y, float z)
{
    p->m_scale.x = x;
    p->m_scale.y = y;
    p->m_scale.z = z;
}

void set_scale_f(t_pipeline *p, float f)
{
    set_scale_3f(p, f, f, f);
}

void set_scale_vec3f(t_pipeline *p, t_vec3f v)
{
    set_scale_3f(p, v.x, v.y, v.z);
}

void set_WorldPos_3f(t_pipeline *p, float x, float y, float z)
{
    p->m_worldPos.x = x;
    p->m_worldPos.y = y;
    p->m_worldPos.z = z;
}

void set_WorldPos_vec3f(t_pipeline *p, t_vec3f v)
{
    p->m_worldPos = v;
}

void set_rotateInfo(t_pipeline *p, float x, float y, float z)
{
    p->m_rotateInfo.x = x;
    p->m_rotateInfo.y = y;
    p->m_rotateInfo.z = z;
}

void set_rotateInfo_vec3f(t_pipeline *p, t_vec3f v)
{
    p->m_rotateInfo = v;
}

void set_PerspectiveProj(t_pipeline *p, PersProjInfo proj)
{
    p->m_persProjInfo = proj;
}

void set_OrthographicProj(t_pipeline *p, OrthoProjInfo *proj)
{
    p->m_orthoProjInfo = p;
}

void set_camera_attr(t_pipeline *p, t_vec3f pos, t_vec3f target, t_vec3f up)
{
    p->m_camera.Pos = p;
    p->m_camera.Target = target;
    p->m_camera.Up = up;
}

void set_camera(t_pipeline *p, t_camera *camera)
{
    set_camera_attr(p, camera->Pos, camera->Target, camera->Up);
}

void init_orientation()
{
    t_orientation orientation;

    orientation.m_scale    = Vector3f(1.0f, 1.0f, 1.0f);
    orientation.m_rotation = Vector3f(0.0f, 0.0f, 0.0f);
    orientation.m_pos      = Vector3f(0.0f, 0.0f, 0.0f);
}

void set_orient(t_pipeline *p, t_orientation o)
{
    p->m_scale = o.m_scale;
    p->m_worldPos = o.m_worldPos;
    p->m_rotateInfo = o.m_rotateInfo;
}

matrix_t GetWorldTrans(t_pipeline p)
{
    matrix_t ScaleTrans = s21_matrix_create(4, 4);
    matrix_t RotateTrans = s21_matrix_create(4, 4);
    matrix_t TranslationTrans = s21_matrix_create(4, 4);

    InitScaleTransform(ScaleTrans, m_scale.x, m_scale.y, m_scale.x);
    InitRotateTransform(RotateTrans, m_rotateInfo.x, m_rotateInfo.y, m_rotateInfo.z);
    InitTranslationTransform(TranslationTrans, m_worldPos.x, m_worldPos.y, m_worldPos.z);

    if (p->m_Wtransformation) {
        s21_free_matrix(p->m_Wtransformation);
    }
    p->m_Wtransformation = s21_mult_matrix(TranslationTrans, RotateTrans);
    matrix_t temp = p->m_Wtransformation;
    p->m_Wtransformation = s21_mult_matrix(p->m_Wtransformation, ScaleTrans);
    s21_free_matrix(temp);
    return p->m_Wtransformation;
}

matrix_t GetViewTrans(t_pipeline *p)
{
    matrix_t CameraTranslationTrans = s21_create_matrix(4,4);
    matrix_t CameraRotateTrans = s21_create_matrix(4,4);

    InitTranslationTransform(CameraTranslationTrans, -m_camera.Pos.x, -m_camera.Pos.y, -m_camera.Pos.z);
    InitCameraTransform_2v(CameraRotateTrans, m_camera.Target, m_camera.Up);
    p->m_Vtransformation = s21_mult_matrix(CameraRotateTrans, CameraTranslationTrans);
    return p->m_Vtransformation;
}

matrix_t GetProjTrans(t_pipeline *p)
{
    InitPersProjTransform(p->m_ProjTransformation, p->m_persProjInfo);
    return p->m_ProjTransformation;
}

matrix_t GetVPTrans(t_pipeline *p)
{
    GetViewTrans(p);
    GetProjTrans(p);
    matrix_t t = p->m_VPtransformation;
    p->m_VPtransformation = s21_mult_matrix(p->m_ProjTransformation, p->m_Vtransformation);
    s21_free_matrix(t);
    return p->m_VPtransformation;
}

matrix_t GetWVPTrans(t_pipeline *p)
{
    GetWorldTrans();
    GetVPTrans();

    p->m_WVPtransformation = s21_mult_matrix(p->m_VPtransformation, p->m_Wtransformation);
    return p->m_WVPtransformation.matrix;
}


