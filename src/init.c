#include "scop.h"

int init_microui(SDL_Window* gWindow, mu_Context *ctx)
{
  /* init microui */
  r_init(gWindow);
  mu_init(ctx);
  ctx->text_width =  text_width;
  ctx->text_height = text_height;
}

int initSDL(t_globals *g)
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
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

int initGL(t_scop *scop)
{
    
    scop->g->p = t_pipeline_new();
    scop->g->pGameCamera = t_camera_new(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    
    //51,76,76,255 - cadetblue / orange
    glClearColor(51.0f / 256.0f, 76.0f/256.0f, 76.0f/256.0f, 1.0f);
    init_mesh_gl(scop->mesh);
    
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

int init(t_scop *scop, char *filename, mu_Context *ctx)
{
    t_mesh *mesh = scop->mesh;
    
    if (filename) {
        load_mesh(mesh, filename);
    } else {
        get_default_mesh(mesh);
    }

    if(!initSDL(scop->g)) {
        printf( "Unable to initialize SDL!\n" );
        return 0;       
    }
    
    if(!initGL(scop))
    {
        printf( "Unable to initialize OpenGL!\n" );
        return 0;
    }
    
    /*
    if (!init_microui(scop->g->gWindow, ctx)) {
        printf( "Unable to initialize microUI!\n" );
        return 0;
    }
    */

    init_mesh_gl(mesh);

    return 1;
}