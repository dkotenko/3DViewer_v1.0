#include "scop.h"

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

set_camera_attr(t_pipeline *p, t_vec3f pos, t_vec3f target, t_vec3f up)
{
    p->m_camera.Pos = p;
    p->m_camera.Target = target;
    p->m_camera.Up = up;
}

void set_camera(t_pipeline *p, t_camera *camera)
{
    set_camera_attr(p, camera->Pos, camera->Target, camera->Up);
}

void set_orient(t_pipeline *p, t_orientation o)
{
    p->m_scale = o.m_scale;
    p->m_worldPos = o.m_worldPos;
    p->m_rotateInfo = o.m_rotateInfo;
}

void set_orient_WorldTrans(t_pipeline *p, WorldTrans *w)
{
    p->m_scale = w->GetScale;
    p->m_worldPos = w->GetRotation;
    p->m_rotateInfo = w->GetPos;
}
