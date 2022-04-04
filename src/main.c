#include "scop.h"
#include "parser.h"
#include "cvector.h"
#include <stdlib.h>
#include <stdio.h>
#include "s21_matrix.h"

t_camera *pGameCamera;
t_pipeline *p;

int init(t_mesh *mesh)
{
    p = t_pipeline_new();
    pGameCamera = t_camera_new(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    
    //51,76,76,255 - cadetblue / orange
    glClearColor(51.0f / 256.0f, 76.0f/256.0f, 76.0f/256.0f, 1.0f);
    init_mesh_gl(mesh);

    if (compile_shaders()) {
        fprintf(stderr, "%s\n", "Error during shader compiling");
        return (0);
    }

    gPersProjInfo.FOV = 60.0f;
    gPersProjInfo.Height = WINDOW_HEIGHT;
    gPersProjInfo.Width = WINDOW_WIDTH;
    gPersProjInfo.zNear = 1.0f;
    gPersProjInfo.zFar = 100.0f;
    if (!run_gui(mesh, filename)) {
        t_camera_free(pGameCamera);
        return (0);    
    }
    t_camera_free(pGameCamera);
    return (1);
}

int main(int ac, char **av)
{
    /*
    if (ac < 2) {
        printf("No files provided: pass .obj file as argument\n");
        exit(0);
    }
    */
    
    char *filename = ac > 1 ? av[1] : NULL;    
    t_mesh mesh = {0};
    init(&mesh, filename);
    mu_Context *ctx = NULL;
    
    run_gui();
}