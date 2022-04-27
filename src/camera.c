#include "scop.h"
#include "vector.h"
#include <stdio.h>
#include <GL/freeglut.h>

t_pipeline *p;
float STEP_SCALE = 1.0f;

void t_camera_free(t_camera *camera)
{
    free(camera);
}

t_camera *t_camera_new()
{
    t_camera *camera;

    camera = (t_camera *)calloc(1, sizeof(t_camera));
    camera->Pos = t_vec3f_new(0.0f, 0.0f, 0.0f);
    camera->Target = Normalize(t_vec3f_new(0.0f, 0.0f, 1.0f));
    camera->Up = Normalize(t_vec3f_new(0.0f, 1.0f, 0.0f));
    return camera;
}

void t_camera_print(t_camera *camera)
{
    printf("Camera:\n");
    t_vec3f_print(camera->Pos, "pos");
    t_vec3f_print(camera->Target, "Target");
    t_vec3f_print(camera->Up, "up");
}

/*
void t_camera_handle_key(t_scop *scop,  t_camera *camera, int key)
{
    if (key == -1) {
        return ;
    }
    t_vec3f temp;
    p = scop->g->p;
    switch (key) {
        case SDLK_RIGHT:
            temp = Cross(camera->Up, camera->Target);
            temp = Normalize(temp);
            temp = t_vec3f_multf(temp, STEP_SCALE);
            camera->Pos = t_vec3f_sum(camera->Pos, temp);
            break ;
        case SDLK_LEFT:
            temp =  Cross(camera->Target, camera->Up);
            temp = Normalize(temp);
            temp = t_vec3f_multf(temp, STEP_SCALE);
            camera->Pos = t_vec3f_sum(camera->Pos, temp);
            break ;
        case SDLK_UP: 
            temp = t_vec3f_multf(camera->Target, STEP_SCALE);
            camera->Pos = t_vec3f_sum(camera->Pos, temp);
            break ;
        case SDLK_DOWN:
            temp = t_vec3f_multf(camera->Target, STEP_SCALE);
            camera->Pos = t_vec3f_sub(camera->Pos, temp);
            break ;
        case GLUT_KEY_PAGE_UP:
            camera->Pos.y += STEP_SCALE;
            break ;
        case GLUT_KEY_PAGE_DOWN:
            camera->Pos.y -= STEP_SCALE;
            break ;
        case SDLK_INSERT:
            p->m_rotateInfo.y += STEP_SCALE;
            break ;
        case SDLK_DELETE:
            p->m_rotateInfo.y -= STEP_SCALE;
            break ;
        case SDLK_HOME:
            p->m_rotateInfo.z += STEP_SCALE;
            break ;
        case SDLK_END:
            p->m_rotateInfo.z -= STEP_SCALE;
            break ;
        case SDLK_PAGEUP:
            p->m_rotateInfo.x += STEP_SCALE;
            break ;
        case SDLK_PAGEDOWN:
            p->m_rotateInfo.x -= STEP_SCALE;
            break ;
        case SDLK_SPACE:
            set_rotateInfo(p, 0.0f, 0.0f, 0.0f);
            break ;
    };
}
*/


