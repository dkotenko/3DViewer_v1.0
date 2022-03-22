#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>
#include "vector.h"
#include "scop.h"
#include "s21_matrix.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

GLuint VBO;
GLuint IBO;
GLuint gWVPLocation;

t_camera *pGameCamera;
PersProjInfo gPersProjInfo;
t_pipeline *p;

static void t_pipeline_print(t_pipeline *p)
{
    PersProjInfo t = p->m_persProjInfo;
    t_vec3f_print(p->m_scale, "m_scale");
    t_vec3f_print(p->m_worldPos, "m_worldPos");
    t_vec3f_print(p->m_rotateInfo, "m_rotateInfo");

    printf("PersProjInfo: FOV:%f Width:%f Height:%f zNear:%f zFar:%f\n",\
    t.FOV, t.Width, t.Height, t.zNear, t.zFar);

    OrthoProjInfo o = p->m_orthoProjInfo;
    printf("OrthoProjInfo: r:%f l:%f b:%f t:%f n:%f f:%f\n",\
    o.r, o.l, o.b, o.t, o.n, o.f);

    t_camera_print(&p->m_camera);
    s21_print_matrix(&p->m_WVPtransformation, "m_WVPtransformation");
    s21_print_matrix(&p->m_VPtransformation, "m_VPtransformation");
    s21_print_matrix(&p->m_WPtransformation, "m_WPtransformation");
    s21_print_matrix(&p->m_WVtransformation, "m_WVtransformation");
    s21_print_matrix(&p->m_Wtransformation, "m_Wtransformation");
    s21_print_matrix(&p->m_Vtransformation, "m_Vtransformation");
    s21_print_matrix(&p->m_ProjTransformation, "m_ProjTransformation");
}

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    static float scale = 0.0f;
    static float delta = 0.1f;
    scale += delta;

    p = t_pipeline_new();

    //set_rotateInfo(p, 0.0f, scale, 0.0f);
    set_WorldPos_3f(p, 0.0f, 0.0f, 3.0f);
    set_camera(p, pGameCamera);
    set_PerspectiveProj(p, gPersProjInfo);
    
    const GLfloat* WVPTrans = (const GLfloat*)GetWVPTrans(p);
    /* for (int i = 0; i < 16; i++) {
        printf("%f ", WVPTrans[i]);
    }
    printf("\n");
    */

    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, WVPTrans);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
    //t_pipeline_print(p);
    //exit(0);
}

static void SpecialKeyboardCB(int key, int x, int y)
{
    //OGLDEV_KEY Ogldevkey = GLUTkeyToOGLDEVkey(key);
    //pGameCamera->Onkeyboard(key);
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
    glutDisplayFunc(RenderSceneCB);
    glutIdleFunc(RenderSceneCB);
    glutSpecialFunc(SpecialKeyboardCB);
    glutKeyboardFunc(NonSpecialKeyboardCB);
}


int handle_glut(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    int win = glutCreateWindow("3DViewer_V1.0");

    
    InitializeGlutCallbacks();
    pGameCamera = t_camera_new(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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
    t_camera_free(pGameCamera);
    return 0;
}