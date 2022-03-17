#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>
#include "vector.h"
#include "scop.h"
#include "s21_matrix.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

GLuint VBO;
GLuint IBO;
GLuint gWVPLocation;

t_camera *pGameCamera = NULL;
PersProjInfo gPersProjInfo;

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    static float scale = 0.0f;
    static float delta = 0.01f;

    scale += delta;

    Pipeline p;
    set_rotateInfo(&p, 0.0f, Scale, 0.0f);
    set_WorldPos_3f(&p, 0.0f, 0.0f, 3.0f);
    set_camera(&p, pGameCamera);
    set_PerspectiveProj(&p, gPersProjInfo);
    
    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, (const GLfloat*)p.m_WVPtransformation.matrix);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}

static void _SpecialKeyboardCB(int Key, int x, int y)
{
    OGLDEV_KEY OgldevKey = GLUTKeyToOGLDEVKey(Key);
    pGameCamera->OnKeyboard(OgldevKey);
}


static void CreateVertexBuffer()
{
    t_vec3f vertices[4];

    vertices[0] = t_vec3f_new(-1.0f, -1.0f, 0.5773f);
    vertices[1] = t_vec3f_new(0.0f, -1.0f, -1.15475f);
    vertices[2] = t_vec3f_new(1.0f, -1.0f, 0.5773f);
    vertices[3] = t_vec3f_new(0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

static void CreateIndexBuffer()
{
    unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               0, 1, 2 };
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

static void InitializeGlutCallbacks()
{
    glutDisplayFunc(_RenderSceneCB);
    glutIdleFunc(_RenderSceneCB);
    glutSpecialFunc(_SpecialKeyboardCB);
}


int handle_glut(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    int win = glutCreateWindow("3DViewer_V1.0");

    InitializeGlutCallbacks();
    t_camera *camera = t_camera_create(WINDOW_WIDTH, WINDOW_HEIGHT);
    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    CreateVertexBuffer();
    CreateIndexBuffer();

    if (compile_shaders()) {
        fprintf(stderr, "%s\n", "Error during shader compiling");
    }

    gPersProjInfo.FOV = 60.0f;
    gPersProjInfo.Height = WINDOW_HEIGHT;
    gPersProjInfo.Width = WINDOW_WIDTH;
    gPersProjInfo.zNear = 1.0f;
    gPersProjInfo.zFar = 100.0f;


    glutMainLoop();
    t_camera_free(camera);
    return 0;
}