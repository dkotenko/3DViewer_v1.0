#include "scop.h"
#include "microui.h"

bool is_running;

void handleKeys(t_scop *scop)
{
    const		Uint8 *s = scop->g->state;
    int key = -1;

    if (s[SDL_SCANCODE_DOWN]) {
        key = SDLK_DOWN;
    } else if (s[SDL_SCANCODE_UP]) {
        key = SDLK_UP;
    } else if (s[SDL_SCANCODE_LEFT]) {
        key = SDLK_LEFT;
    } else if (s[SDL_SCANCODE_RIGHT]) {
        key = SDLK_RIGHT;
    }
    t_camera_handle_key(scop, scop->g->pGameCamera, key);
}

void render_scene(t_scop *scop)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    set_WorldPos_3f(scop->g->p, 0.0f, 0.0f, 3.0f);
    set_camera(scop->g->p, scop->g->pGameCamera);
    set_PerspectiveProj(scop->g->p, scop->g->gPersProjInfo);
    
    const GLfloat* WVPTrans = (const GLfloat*)GetWVPTrans(scop->g->p);
    glUniformMatrix4fv(scop->g->gWVPLocation, 1, GL_TRUE, WVPTrans);
    draw_mesh(scop->mesh);
}

void clean_after_run(t_globals *g)
{
	//glDeleteProgram(gProgramID);
	SDL_DestroyWindow(g->gWindow);
	g->gWindow = NULL;
	SDL_Quit();
}



int run(t_scop *scop) {

  is_running = true;
  SDL_Event e = {0};
  SDL_StartTextInput();
  while (is_running) {
    
    while (SDL_PollEvent(&e)) {

      if (e.key.keysym.sym == SDLK_ESCAPE) {
          is_running = false;
      } else if (e.type == SDL_KEYDOWN)
        {
            handleKeys(scop);
        }
    }
    render_scene(scop);
    SDL_GL_SwapWindow (scop->g->gWindow);
  }   
  SDL_StopTextInput();
  clean_after_run(scop->g);
  return (1);
}