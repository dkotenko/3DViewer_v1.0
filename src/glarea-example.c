//#include <stdio.h>
//#include <string.h>
//#include <iostream>

//#include <glib.h>


#include <scop.h>
#define IGNORE_VAR(type, identifier) \
{ \
  type IGNORED_VARIABLE_abcd = identifier; \
  identifier = IGNORED_VARIABLE_abcd; \
}
t_scop *scop;

t_scop *create_scop() {
  t_scop *scop =  calloc(1, sizeof(t_scop));
  scop->mesh = ft_memalloc(sizeof(t_mesh));
  scop->g = ft_memalloc(sizeof(t_globals));
  scop->g->filename = ft_strdup("resources/42.obj");;// filename ? ft_strdup(filename) : NULL;
  scop->g->texture_filename = ft_strdup("resources/texture.jpg");
  scop->config = calloc(1, sizeof(t_config));
  return scop;
}

static gboolean realise(GtkGLArea *area, GdkGLContext *context) //, gpointer data)
{
  IGNORE_VAR(GdkGLContext*, context);

  //char *filename = (char *)data;
  scop = create_scop();
  gtk_gl_area_make_current(GTK_GL_AREA(area));
  
  //printf("%s\n",scop->g->filename);
  
  init(scop, scop->g->filename);
  
  if (gtk_gl_area_get_error (GTK_GL_AREA(area)) != NULL)
  {
    printf("failed to initialiize buffers\n");
    return false;
  }
  return true;
}

/*
** render, obviously
*/


static gboolean render(GtkGLArea *area, GdkGLContext *context)
  {
  IGNORE_VAR(GdkGLContext*, context);
  IGNORE_VAR(GtkGLArea*, area);
  
  //glEnable(GL_DEPTH_TEST);
  //glEnable(GL_BLEND);

  glClearColor(51.0f / 256.0f, 76.0f/256.0f, 76.0f/256.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  draw_mesh(scop);
  
  glFlush();
  return TRUE;
}



int main(int argc, char** argv)
{ 
  gtk_init(&argc, &argv);
  
  GtkWidget *window  = gtk_window_new(GTK_WINDOW_TOPLEVEL),
            *gl_area = gtk_gl_area_new();
  
  //char *init_filename = argc > 1 ? ft_strdup(argv[1]) : NULL;
  //gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);
  g_signal_connect(window,  "delete-event", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(gl_area, "realize",      G_CALLBACK(realise),       NULL);
  g_signal_connect(gl_area, "render",       G_CALLBACK(render),        NULL);
  
  gtk_container_add(GTK_CONTAINER(window), gl_area);
  
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}