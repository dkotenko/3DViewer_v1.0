#include "scop.h"
#include "vector.h"

void t_camera_free(t_camera *camera)
{
    free(camera);
}

t_camera *t_camera_new(int width, int height)
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
    t_vec3f_print(camera->Pos, "pos");
    t_vec3f_print(camera->Target, "Target");
    t_vec3f_print(camera->Up, "up");
}


