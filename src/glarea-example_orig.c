//#include <stdio.h>
//#include <string.h>
//#include <iostream>

//#include <glib.h>

#include <gdk/gdkx.h>
#include <epoxy/glx.h>
#include <epoxy/gl.h>
#include <gtk/gtk.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>





const GLchar *vert_src ="\n" \
"#version 330                                  \n" \
"          #extension GL_ARB_explicit_uniform_location : enable                                    \n" \
"                                                   \n" \
"                   out  vec4 knn;                                \n" \
"           layout(location = 0) in vec4 in_position;                                       \n" \
"           layout(location =10)uniform  mat4 projection;                                       \n" \
    "           out  vec4 P;                                       \n" \
"void main()                                   \n" \
"{                                             \n" \
"  gl_Position =  projection*in_position;  \n" \
"knn=in_position  ;  \n" \
"                                                  \n" \
"//  gl_Position =  in_position;  \n" \
"}                                   \n" ;
const GLchar *frag_src ="\n" \
"#version 330                                  \n" \
        "             vec4 b;                                       \n" \
"    in  vec4 knn;                                                \n" \
"void main (void)                              \n" \
"{                                             \n" \
" if(gl_FrontFacing){                               \n" \

"   b= vec4(gl_FragCoord.x/10.0,gl_FragCoord.y/357.0,gl_FragCoord.z*    0.5,1.0);                                                 \n" \
"      gl_FragColor = vec4(0.021,-.1777*(knn.y+2)+0.1+1.21557*knn.x+knn.z  ,1.215*knn.z+0.583*knn.y +.0357*knn.x+3*b.y, 1.0);    \n" \
"       }                                    \n" \
"else  discard; \n" \
"                                                   \n" \
"                                                   \n" \
"}                                            \n";




GLfloat t[16]={ 1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1};
glm::mat4 yt,b;


GLuint gl_vao, gl_buffer, gl_program;

static gboolean realise(GtkGLArea *area, GdkGLContext *context)
{


  gtk_gl_area_make_current(GTK_GL_AREA(area));
  if (gtk_gl_area_get_error (GTK_GL_AREA(area)) != NULL)
  {
    printf("failed to initialiize buffers\n");
    return false;
  }

  GLfloat verts[] = 
  {   
     +0.7,+0.7,+0.7, 
         -0.7,0.7, 0.7,
         -0.7,+0.7, -0.7,

         0.7,+0.7, -0.7,
         +0.7,+0.7,+0.7,
         -0.7,+0.7, -0.7,

         -0.7,-0.7, +0.7,
         +0.7,+0.7,+0.7,
        -0.7,0.7, 0.7,

         +0.7,+0.7,+0.7,
         -0.7,-0.7, +0.7,
         0.7,-0.7, 0.7,

         +0.7,-0.7,-0.7,
         -0.7,-0.7,-0.7,
         0.7,+0.7, -0.7,

       -0.7,+0.7, -0.7,
    0.7,+0.7, -0.7,
       -0.7,-0.7, -0.7,



         -0.7,-0.7, +0.7,
    -0.7,-0.7, -0.7,
         0.7,-0.7, 0.7,



+0.7,-0.7, -0.7,

0.7,-0.7, 0.7,

-0.7,-0.7, -0.7,

                  0.7,+0.7, -0.7,
         +0.7,+0.7,+0.7,
+0.7,-0.7, -0.7,

         0.7,-0.7, -0.7,
              +0.7,+0.7,+0.7,
 
 
  0.7,-0.7, 0.7,


                 -0.7,-0.7, -0.7,
        -0.7,0.7, 0.7,
 -0.7,+0.7, -0.7,



         -0.7,-0.7, +0.7,
        -0.7,0.7, 0.7,
         -0.7,-0.7, -0.7

  };
b=glm::lookAt(glm::vec3(1.75,-2.38,1.4444), glm::vec3( 0., 0., 0.),glm::vec3( 0.,0.2,-00.));
yt=glm::perspective(45., 1., 1.2, 300.);
b=yt*b*glm::mat4(1.);

//b=glm::lookAt(glm::vec3(0., 0.,-1.),glm::vec3( 0., 0., 0.),glm::vec3( 0.,025.,-1.));
//yt=yt*b;





  GLuint frag_shader, vert_shader;
  frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  vert_shader = glCreateShader(GL_VERTEX_SHADER);


  glShaderSource(frag_shader, 1, &frag_src, NULL);
  glShaderSource(vert_shader, 1, &vert_src, NULL);

  glCompileShader(frag_shader);
  glCompileShader(vert_shader);

  gl_program = glCreateProgram();
  glAttachShader(gl_program, frag_shader);
  glAttachShader(gl_program, vert_shader);
  glLinkProgram(gl_program);

// glUniformMatrix4fv(1, 1, 0, glm::value_ptr(b));

  glGenVertexArrays(1, &gl_vao);
  glBindVertexArray(gl_vao);



  glGenBuffers(1, &gl_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, gl_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);



  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glBindVertexArray(0);
  

  return TRUE;
}

static gboolean render(GtkGLArea *area, GdkGLContext *context)
{
 


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 1.0);



  glUseProgram(gl_program);
 glUniformMatrix4fv(10, 1, 0, &b[0][0]);


  glBindVertexArray(gl_vao);


  glDrawArrays(GL_TRIANGLES,0,36 );

  glBindVertexArray (0);
  glUseProgram (0);


  glFlush();

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