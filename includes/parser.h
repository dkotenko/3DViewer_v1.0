#ifndef PARSER_H
#define PARSER_H

#include "vector.h"
//#include <GL/glew.h>
//#include <GL/freeglut.h>
#include <stdio.h>

#define BUFFERS_SIZE_IN_ELEMENTS 3

enum BUFFER_TYPE {
        INDEX_BUFFER,
        POS_VB,
        TEXCOORD_VB,
        NORMAL_VB,
        //WVP_MAT_VB   = 4,  // required only for instancing
        //WORLD_MAT_VB = 5,  // required only for instancing
        NUM_BUFFERS
};

typedef struct {
	int vertex;
	int texture;
	int normal;
} t_vertex_index;

typedef struct {
	t_vec3f vertex;
	t_vec2f texture;
	t_vec3f normal;
} t_vertex;

typedef struct {
	t_vertex *vertices;
	int vertex_num;
	GLuint VB;
    GLuint IB;
	int NumIndices;
} t_face;

typedef struct {
	t_vertex_index *indices;
	int indices_num;
} t_face_transport;

typedef struct {
    GLenum type;
    char *filename;
    GLuint obj;
    int width;
    int height;
    int bpp;
} t_texture;

typedef struct {
	t_vertex *vertices_to_draw;
	unsigned int *indices_to_draw;
	t_vertex *vertices_orig;
	t_vec3f *vertices;
	t_vec3f *normals;
	t_vec2f *textures;
	t_vec3f *all_vertices;
	t_vec3f *all_normals;
	t_vec2f *all_textures;
	t_face *faces;
	t_face_transport *faces_transport;
	int material_index;
	GLuint VAO;
	t_texture *texture;
	GLuint buffers[NUM_BUFFERS];
} t_mesh;

typedef struct {
} t_mesh_transport;

typedef struct s_object_node{
	struct s_object_node *children;
	int *m111eshes_indexes;
} t_obj_node;

typedef struct {
	int (*f)(void);
} t_material;

typedef struct {
	t_obj_node *root_node;
	t_mesh *m111eshes;
	t_material *materials;
} t_obj;

int parse_file(char *filename, t_mesh *mesh);
void get_default_mesh(t_mesh *mesh);
void populate_f(t_mesh *mesh);

#endif