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
	t_vx_index *vxs;
	int vx_num;
} t_face;

typedef struct {
	t_vec3 *vertices;
	t_vec2 *normals;
	t_vec3 *textures;
	t_face *faces;
	int material_index;
} t_mesh;

typedef struct {
	t_obj_node *children;
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

#endif