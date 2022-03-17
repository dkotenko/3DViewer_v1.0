#ifndef SCOP_H
#define SCOP_H

typedef struct {

} t_camera;

struct PersProjInfo
{
    float FOV;
    float Width;
    float Height;
    float zNear;
    float zFar;
};

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
int handle_glut(int ac, char **av);
int compile_shaders();

t_camera *t_camera_new(int width, int height);
void t_camera_free(t_camera *camera);

#endif