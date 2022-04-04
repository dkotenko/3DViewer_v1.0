#ifndef SCOP_H
#define SCOP_H

#include <stdbool.h>
#include "vector.h"
#include "s21_matrix.h"
#include "parser.h"
#include <stdio.h>

#define DEBUG 0
#define WINDOW_WIDTH 640       
#define WINDOW_HEIGHT 480
#define WINDOW_START_X 200
#define WINDOW_START_Y 100
#define APP_NAME "3DViewer_V1.0"



#define here() printf("HERE\n");

typedef struct {
    t_vec3f Pos;
    t_vec3f Target;
    t_vec3f Up;
} t_camera;

typedef struct 
{
    float FOV;
    float Width;
    float Height;
    float zNear;
    float zFar;
} PersProjInfo;

typedef struct 
{
    float r;        // right
    float l;        // left
    float b;        // bottom
    float t;        // top
    float n;        // z near
    float f;        // z far
} OrthoProjInfo;

typedef struct 
{
    t_vec3f m_scale;
    t_vec3f m_rotateInfo;
    t_vec3f m_worldPos;
} t_orientation;

typedef struct {
    t_vec3f m_scale;
    t_vec3f m_worldPos;
    t_vec3f m_rotateInfo;

    PersProjInfo m_persProjInfo;
    OrthoProjInfo m_orthoProjInfo;

    t_camera m_camera;
    matrix_t m_WVPtransformation;
    matrix_t m_VPtransformation;
    matrix_t m_WPtransformation;
    matrix_t m_WVtransformation;
    matrix_t m_Wtransformation;
    matrix_t m_Vtransformation;
    matrix_t m_ProjTransformation; 
} t_pipeline;


char *read_file(char *filename);
int handle_glut(t_mesh *mesh);
int compile_shaders();

t_camera *t_camera_new(int width, int height);
void t_camera_free(t_camera *camera);
void t_camera_print(t_camera *camera);

/*
** glut.c
*/
void GLUTBackendInit(int argc, char **argv);
bool GLUTBackendCreateWindow(unsigned int Width, unsigned int Height, bool isFullScreen, const char* pTitle);

/*
** pipeline.c
*/
t_pipeline *t_pipeline_new();
t_pipeline t_pipeline_init();
void set_scale_3f(t_pipeline *p, float x, float y, float z);
void set_scale_f(t_pipeline *p, float f);
void set_scale_vec3f(t_pipeline *p, t_vec3f v);
void set_WorldPos_3f(t_pipeline *p, float x, float y, float z);
void set_WorldPos_vec3f(t_pipeline *p, t_vec3f v);
void set_rotateInfo(t_pipeline *p, float x, float y, float z);
void set_rotateInfo_vec3f(t_pipeline *p, t_vec3f v);
void set_PerspectiveProj(t_pipeline *p, PersProjInfo proj);
void set_OrthographicProj(t_pipeline *p, OrthoProjInfo *proj);
void set_camera_attr(t_pipeline *p, t_vec3f pos, t_vec3f target, t_vec3f up);
void set_camera(t_pipeline *p, t_camera *camera);
void set_orient(t_pipeline *p, t_orientation o);

matrix_t GetWorldTrans(t_pipeline *p);
matrix_t GetViewTrans(t_pipeline *p);
matrix_t GetProjTrans(t_pipeline *p);
matrix_t GetVPTrans(t_pipeline *p);
float *GetWVPTrans(t_pipeline *p);

/*
** math.c
*/

void InitRotationX(matrix_t *ScaleTrans, float x);
void InitRotationY(matrix_t ScaleTrans, float y);
void InitRotationZ(matrix_t ScaleTrans, float z);
void InitScaleTransform(matrix_t *ScaleTrans, float ScaleX, float ScaleY, float ScaleZ);
void InitRotateTransform(matrix_t *m, float RotateX, float RotateY, float RotateZ);
void InitTranslationTransform(matrix_t *matrix, float x, float y, float z);
void InitOrthoProjTransform(matrix_t matrix, OrthoProjInfo p);
void InitPersProjTransform(matrix_t ProjTransformation, PersProjInfo p);
void InitTranslationTransform_vec3d(matrix_t CameraTranslationTrans, const t_vec3f Pos);
void InitCameraTransform_2v(matrix_t *CameraRotateTrans, const t_vec3f Target, const t_vec3f Up);
void InitCameraTransform_3v(matrix_t *CameraRotateTrans, t_vec3f Pos, t_vec3f Target, t_vec3f Up);
t_vec3f Cross(t_vec3f vector, t_vec3f v);
t_vec3f Normalize(t_vec3f v);
void t_camera_handle_key(t_camera *camera, int key);

/*
** mesh.h
*/
void print_mesh(t_mesh *mesh);
void t_face_transport_print(t_face_transport *t, char *label);
void t_face_print(t_face *face, char *label);
void t_vertex_index_print(t_vertex_index vi);
void t_vertex_print(t_vertex vertex);
void init_mesh_gl(t_mesh *mesh);
void t_pipeline_print(t_pipeline *p);
void clear_mesh(t_mesh *mesh);
bool load_mesh(t_mesh *mesh, char *filename);

/*
**
*/
int run_gui(t_mesh *mesh, char *filename);
#endif