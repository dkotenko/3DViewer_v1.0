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

int (*length)(void);


typedef struct {
	
} t_vertex;

typedef struct {

} t_mesh;

typedef struct {
	t_obj_node *children;
	t_mesh *meshes;
} t_obj_node;

typedef struct {
	
} t_obj;

#endif