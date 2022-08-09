#ifndef PARSER_H
#define PARSER_H

#include "vector.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>

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
	t_face *faces;
	t_face_transport *faces_transport;
	int material_index;
	GLuint VB;
    GLuint IB;
	t_texture *texture;
} t_mesh;

typedef struct s_scene_node{
	struct s_object_node *children;
	int *meshes_indexes;
} t_scene_node;

typedef struct {
	char	*name;
	t_texture	texture;
	t_vec3f		ambient;
	t_vec3f		diffuse;
	t_vec3f		specular;
	float		specular_exponent;
	float		alpha;
} t_material;

typedef struct {
	t_vec3f	pos;
	float	scale;
	matrix_t	rotation;
	matrix_t	transformation;
	t_vec3f		min;
	t_vec3f		max;
	t_vec3f		size;
	t_vec3f		center;
} t_model_data;

typedef struct {
	t_scene_node *root_node;
	t_mesh *meshes;
	t_material *materials;
	t_model_data	*d;
	int	mod_from;
	int	mod_to;
	float	mod_transition;
} t_model;

typedef struct s_scene {
	t_scene_node	*root_node;
	t_mesh			*meshes;
	t_material		*materials;
} t_scene;

int parse_file(char *filename, t_mesh *mesh);
void get_default_mesh(t_mesh *mesh);
void populate_f(t_mesh *mesh);

#endif