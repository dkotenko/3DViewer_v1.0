#ifndef PARSER_H
#define PARSER_H

typedef struct {
	float x;
	float y;
} t_vec2;

typedef struct {
	float x;
	float y;
	float z;
} t_vec3;

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
	t_vec3 *vertices;
	t_vec3 *normals;
	t_vec2 *textures;
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
t_vec3 t_vec3_new(float x, float y, float z);
t_vec2 t_vec2_new(float x, float y);

#endif