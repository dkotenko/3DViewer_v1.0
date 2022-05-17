#include "scop.h"
#include "cvector.h"
#include <string.h>

int initGL(t_scop *scop)
{
    
    scop->g->p = t_pipeline_new();
    //printf("%d\n", scop->g->p == NULL); 
    scop->g->pGameCamera = t_camera_new(scop->config->window_width,\
    scop->config->window_height);
    
    
    //51,76,76,255 - cadetblue / orange
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    //glEnable(GL_MULTISAMPLE);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
    
    if (compile_shaders(scop->g)) {
        fprintf(stderr, "%s\n", "Error during shader compiling");
        return (0);
    }
    scop->g->gPersProjInfo.FOV = 60.0f;
    scop->g->gPersProjInfo.Height = scop->config->window_height;
    scop->g->gPersProjInfo.Width = scop->config->window_width;
    scop->g->gPersProjInfo.zNear = 1.0f;
    scop->g->gPersProjInfo.zFar = 100.0f;
    
    return 1;
}


void init_config(t_config *config)
{
    //default values
    
    config->window_width = 640;
    config->window_height = 480;
    config->debug = 0;
    config->window_start_x = 200;
    config->window_start_y = 100;
    config->app_name = ft_strdup("3DViewer_V1.0");
    
    parse_config_file(config);
}

int init(t_scop *scop, char *filename)
{
    t_mesh *mesh = scop->mesh;

    init_config(scop->config);
    if(!initGL(scop))
    {
        printf( "Unable to initialize OpenGL!\n" );
        return 0;
    }
    GLerror("before load mesh");
    load_mesh(mesh, filename);
    GLerror("after load mesh");
    t_texture *t = t_texture_new(GL_TEXTURE_2D, scop->g->texture_filename);
    t_texture_load(t);
    mesh->texture = t;
    
    //init_gl_buffers(mesh);

    return 1;
}