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
	int vertex_num;
} t_face_transport;

typedef struct {
	t_vec3f *vertices;
	t_vec3f *normals;
	t_vec2f *textures;
	t_face *faces;
	t_face_transport *faces_transport;
	int material_index;
} t_mesh;

typedef struct {
} t_mesh_transport;

typedef struct s_object_node{
	struct s_object_node *children;
	int *meshes_indexes;
} t_obj_node;

typedef struct {
	int (*f)(void);
} t_material;

typedef struct {
	t_obj_node *root_node;
	t_mesh *meshes;
	t_material *materials;
} t_obj;

int parse_file(char *filename, t_mesh *mesh);
void print_parse_result(t_mesh *mesh);
t_mesh t_mesh_init_zeroes();
void draw_mesh(t_mesh *mesh);
void get_default_mesh(t_mesh *mesh);
void populate_f(t_mesh *mesh);
#endif