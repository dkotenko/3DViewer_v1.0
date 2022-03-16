#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>
#include "vector.h"
#include "scop.h"
#include "s21_matrix.h"

GLuint VBO;
GLint gTranslationLocation;

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    static float scale = 0.0f;
    static float delta = 0.005f;

    scale += delta;
    if (scale >= 1.0f || scale <= -1.0f) {
        delta *= -1.0f;
    }
    
    matrix_t translation = s21_create_matrix(4,4);
    float values[4][4] = {
        {1.0f, 0.0f, 0.0f, scale},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    for (int i = 0; i < 4; i++) {
        memcpy(translation.matrix[i], values[i], sizeof(float));
    }
    
    
    glUniformMatrix4fv(gTranslationLocation, 1, GL_TRUE, &values[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    glutPostRedisplay();

    glutSwapBuffers();
}


static void CreateVertexBuffer()
{
    t_vec3f vertices[3];

    vertices[0] = t_vec3f_new(-1.0f, -1.0f, 0.0f);
    vertices[1] = t_vec3f_new(1.0f, -1.0f, 0.0f);
    vertices[2] = t_vec3f_new(0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}


int handle_glut(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    int width = 640;
    int height = 480;
    glutInitWindowSize(width, height);

    int x = 200;
    int y = 100;
    glutInitWindowPosition(x, y);
    int win = glutCreateWindow("3DViewer_V1.0");

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    CreateVertexBuffer();

    if (compile_shaders()) {
        fprintf(stderr, "%s\n", "Error during shader compiling");
    }

    glutDisplayFunc(RenderSceneCB);

    glutMainLoop();

    return 0;
}