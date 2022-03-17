#include "scop.h"

void t_camera_free(t_camera *camera)
{
    free(camera);
}

t_camera *t_camera_new(int width, int height)
{
    t_camera *camera;

    camera = (t_camera *)calloc(1, sizeof(t_camera));
    return camera;
}

