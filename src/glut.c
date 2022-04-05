#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>
#include "vector.h"
#include "cvector.h"
#include "scop.h"
#include "s21_matrix.h"

extern GLuint gWVPLocation;

t_camera *pGameCamera;
PersProjInfo gPersProjInfo;
t_pipeline *p;
t_mesh *g_mesh;

enum {
    POINT,
    TRIANGLE,
    NUM
} e_prim_types;

#define DRAW_PRIMITIVE TRIANGLE
static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //set_rotateInfo(p, 0.0f, scale, 0.0f);
    set_WorldPos_3f(p, 0.0f, 0.0f, 3.0f);
    set_camera(p, pGameCamera);
    set_PerspectiveProj(p, gPersProjInfo);
    
    const GLfloat* WVPTrans = (const GLfloat*)GetWVPTrans(p);
    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, WVPTrans);
    //print_mesh(g_mesh);
    //exit(0);
    draw_mesh(g_mesh);
    glutSwapBuffers();
    /*
    if (DRAW_PRIMITIVE == POINT) {
        glDrawArrays(GL_POINTS, 0, 12);
        glEnable(GL_PROGRAM_POINT_SIZE);
    } else {
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    */
    
}

static void SpecialKeyboardCB(int key, int x, int y)
{
    t_camera_handle_key(pGameCamera, key);
    //printf("special key_num:%d x:%d y:%d\n", key, x, y);
}

#define _KEY_ESCAPE 27

static void NonSpecialKeyboardCB(unsigned char key, int x, int y)
{
    if (key == _KEY_ESCAPE) {
        exit(0);
    }
    t_camera_handle_key(pGameCamera, key);
    //printf("ordinary key_num:%d x:%d y:%d\n", key, x, y);
}

static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
    glutIdleFunc(RenderSceneCB);
    glutSpecialFunc(SpecialKeyboardCB);
    glutKeyboardFunc(NonSpecialKeyboardCB);
}

void GLUTBackendInit(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
}

bool GLUTBackendCreateWindow(unsigned int Width, unsigned int Height, bool isFullScreen, const char* pTitle)
{
    if (isFullScreen) {
        char ModeString[64] = { 0 };
        int bpp = 32;
        snprintf(ModeString, sizeof(ModeString), "%dx%d:%d@60", Width, Height, bpp);
        glutGameModeString(ModeString);
        glutEnterGameMode();
    }
    else {
        glutInitWindowPosition(WINDOW_START_X, WINDOW_START_Y);
        glutInitWindowSize(Width, Height);
        glutCreateWindow(pTitle);
    }

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return false;
    }

    return true;
}

int handle_glut(t_mesh *mesh)
{
    g_mesh = mesh;
    p = t_pipeline_new();
    pGameCamera = t_camera_new(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    
    //51,76,76,255 - cadetblue / orange
    glClearColor(51.0f / 256.0f, 76.0f/256.0f, 76.0f/256.0f, 1.0f);
    init_mesh_gl(g_mesh);

    if (compile_shaders()) {
        fprintf(stderr, "%s\n", "Error during shader compiling");
    }

    gPersProjInfo.FOV = 60.0f;
    gPersProjInfo.Height = WINDOW_HEIGHT;
    gPersProjInfo.Width = WINDOW_WIDTH;
    gPersProjInfo.zNear = 1.0f;
    gPersProjInfo.zFar = 100.0f;

    InitializeGlutCallbacks();
    glutMainLoop();
    t_camera_free(pGameCamera);
    return 0;
}