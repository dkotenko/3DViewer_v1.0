#ifndef PARSER_H
#define PARSER_H

#include "vector.h"

typedef struct {
	int vertex;
	int texture;
	int normal;
} t_vx_index;

typedef struct {
	t_vx_index *indices;
	int vertex_num;
} t_face;

typedef struct {
	t_vec3f *vertices;
	t_vec3f *normals;
	t_vec2f *textures;
	t_face *faces;
	int material_index;
} t_mesh;

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


#endif