//#include <stdio.h>
//#include <string.h>
//#include <iostream>

//#include <glib.h>


#include <scop.h>

t_config *g_config;
char *filename;
t_scop *scop;

static gboolean realise(GtkGLArea *area, int argc, char **argv)
{

  
  gtk_gl_area_make_current(GTK_GL_AREA(area));
  
  if (gtk_gl_area_get_error (GTK_GL_AREA(area)) != NULL)
  {
    printf("failed to initialiize buffers\n");
    return false;
  }
  
  filename = argc > 1 ? argv[1] : NULL;
      
  scop = calloc(1, sizeof(t_scop));
  scop->mesh = calloc(1, sizeof(t_mesh));
  scop->g = calloc(1, sizeof(t_globals));
  scop->config = calloc(1, sizeof(t_config));
  scop->g->texture_filename = ft_strdup("resources/texture.jpg");
  g_config = scop->config;
  
  init(scop, filename);
  
  //init all
  return true;
}

static gboolean render(t_scop *scop)
{
 
  //render, obviously
  draw_mesh(scop);
  printf("%d\n",scop->g->gWVPLocation);
  return TRUE;
}

int main(int argc, char** argv)
{  
  gtk_init(&argc, &argv);
  
  GtkWidget *window  = gtk_window_new(GTK_WINDOW_TOPLEVEL),
            *gl_area = gtk_gl_area_new();
  
  g_signal_connect(window,  "delete-event", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(gl_area, "realize",      G_CALLBACK(realise),       NULL);
  g_signal_connect(gl_area, "render",       G_CALLBACK(render),        NULL);
  
  gtk_container_add(GTK_CONTAINER(window), gl_area);
  
  gtk_widget_show_all(window);
  
  gtk_main();

  return 0;
}