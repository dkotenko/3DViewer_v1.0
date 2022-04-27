//#include <stdio.h>
//#include <string.h>
//#include <iostream>

//#include <glib.h>


#include <scop.h>

static gboolean realise(GtkGLArea *area, GdkGLContext *context, gpointer data)
{
  t_scop *scop = (t_scop *)data;
  (void)context;
  gtk_gl_area_make_current(GTK_GL_AREA(area));
  init(scop, scop->g->filename);
  here();
  
  if (gtk_gl_area_get_error (GTK_GL_AREA(area)) != NULL)
  {
    printf("failed to initialiize buffers\n");
    return false;
  }
  
  printf("%s\n", scop->g->filename);
  exit(0);
  
  
  //init all
  return true;
}

static gboolean render(GtkGLArea *area, GdkGLContext *context, gpointer data)
{
  //render, obviously
  (void)area;
  (void)context;
  t_scop *scop = (t_scop *)data;
  draw_mesh(scop);
  printf("%d\n",scop->g->gWVPLocation);
  return TRUE;
}

void init_scop(t_scop *scop, int argc, char **argv) {
  scop = calloc(1, sizeof(t_scop));
  
  scop->mesh = calloc(1, sizeof(t_mesh));
  scop->g = calloc(1, sizeof(t_globals));
  scop->g->filename = argc > 1 ? argv[1] : NULL;
  scop->g->texture_filename = ft_strdup("resources/texture.jpg");
  scop->config = calloc(1, sizeof(t_config));
}

int main(int argc, char** argv)
{ 
  t_scop *scop = NULL;
  init_scop(scop, argc, argv);
  printf("%s\n", scop->g->filename);
  gtk_init(&argc, &argv);
  
  GtkWidget *window  = gtk_window_new(GTK_WINDOW_TOPLEVEL),
            *gl_area = gtk_gl_area_new();
  

  g_signal_connect(window,  "delete-event", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(gl_area, "realize",      G_CALLBACK(realise),       scop);
  g_signal_connect(gl_area, "render",       G_CALLBACK(render),        scop);
  
  gtk_container_add(GTK_CONTAINER(window), gl_area);
  
  

  gtk_widget_show_all(window);
  
  gtk_main();

  return 0;
}