#include "scop.h"
#include "cvector.h"
#include <string.h>

int init_microui(SDL_Window* gWindow, mu_Context **ctx)
{
  /* init microui */
  r_init(gWindow);
  mu_Context *ctx_new = malloc(sizeof(mu_Context));
  mu_init(ctx_new);
  ctx_new->text_width =  text_width;
  ctx_new->text_height = text_height;
  *ctx = ctx_new;
}

int initSDL(t_globals *g)
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    return 0;
  }
  
  g->gWindow = SDL_CreateWindow( APP_NAME, WINDOW_START_X, WINDOW_START_Y, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
  if( g->gWindow == NULL )
  {
    printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
    return (0);
  }

  g->gContext = SDL_GL_CreateContext(g->gWindow);
  if( g->gContext == NULL )
  {
    printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
    return 0;
  }
  g->state = SDL_GetKeyboardState(NULL);
  glewExperimental = GL_TRUE; 
  GLenum glewError = glewInit();
  if( glewError != GLEW_OK )
  {
    printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
    return 0;
  }
  return (1);
}

void init_gl_buffers(t_mesh *mesh)
{
    //NumIndices = Indices.size();
    int vertices_size = cvector_size(mesh->vertices_to_draw);
    
    glGenBuffers(1, &mesh->VB);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(t_vertex) * vertices_size, mesh->vertices_to_draw, GL_STATIC_DRAW);
        
    /*
        glGenBuffers(1, &IB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &Indices[0], GL_STATIC_DRAW);
    */
}

int initGL(t_scop *scop)
{
    
    scop->g->p = t_pipeline_new();
    //printf("%d\n", scop->g->p == NULL); 
    scop->g->pGameCamera = t_camera_new(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    
    //51,76,76,255 - cadetblue / orange
    glClearColor(51.0f / 256.0f, 76.0f/256.0f, 76.0f/256.0f, 1.0f);
    init_gl_buffers(scop->mesh);
    
    if (compile_shaders(scop->g)) {
        fprintf(stderr, "%s\n", "Error during shader compiling");
        return (0);
    }
    scop->g->gPersProjInfo.FOV = 60.0f;
    scop->g->gPersProjInfo.Height = WINDOW_HEIGHT;
    scop->g->gPersProjInfo.Width = WINDOW_WIDTH;
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
    config->app_name = strdup("3DViewer_V1.0");

    parse_config_file(config);
}

int init(t_scop *scop, char *filename)
{
    t_mesh *mesh = scop->mesh;
    
    if (filename) {
        load_mesh(mesh, filename);
    } else {
        get_default_mesh(mesh);
    }

    init_config(scop->config);

    if(!initSDL(scop->g)) {
        printf( "Unable to initialize SDL!\n" );
        return 0;       
    }
    
    
    if(!initGL(scop))
    {
        printf( "Unable to initialize OpenGL!\n" );
        return 0;
    }    
    
    if (!init_microui(scop->g->gWindow, &scop->g->mui_ctx)) {
        printf( "Unable to initialize microUI!\n" );
        return 0;
    }

    //init_gl_buffers(mesh);

    return 1;
}