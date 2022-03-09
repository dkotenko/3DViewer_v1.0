#include "scop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h> // Библиотека OpenGL
#include <GL/glu.h> // Библиотека GLU
#include "cvector.h"

#define SHOW_CONTENT 0
#define DELIM ' '

#define PATTERN_V "v %lf %lf %lf"
#define PATTERN_VN "vn %lf %lf %lf"
#define PATTERN_VT "vt %lf %lf"
#define PATTERN_F "f %d/%d/%d %d/%d/%d %d/%d/%d"

char dummy_s[100];
/*
typedef struct {
    vec3 *v;
    vec2 *vt;
    vec3 *vn;
} t_f;
*/

typedef struct {
    vec3 vertex;
    vec3 vn;
    vec2 vt;
} t_face_vertex;

typedef struct {
    vec3 *verteces;
    vec2 *uv;
    vec3 *normals;
    int verteces_num;
    int uv_num;
    int normals_num;
    int arr_size;
} t_obj3d;

typedef struct {
    vec3 *verteces;
    vec3 *normals;
    vec2 *textures;
} t_obj;

typedef struct {

} t_face;

void parse_v(char *s, t_obj *obj)
{
    vec3 new;

    sscanf(s, PATTERN_V, dummy_s, &new.x, &new.y, &new.z);
    cvector_push_back(obj->verteces, new);
}

void parse_vt(char *s, t_obj_pars *obj)
{
    vec2 new;

    sscanf(s, PATTERN_VT, dummy_s, &new.x, &new.y);
    cvector_push_back(obj->textures, new);
}

void parse_vn(char *s, t_obj_pars *obj)
{
    vec3 new;

    sscanf(s, PATTERN_VN, dummy_s, &new.x, &new.y, &new.z);
    cvector_push_back(obj->normales, new);
}

void populate_f(t_obj_pars *obj)
{
    t_face face;
    
    sscanf(s, PATTERN_VN, dummy_s, &new.x, &new.y, &new.z);

    
    t_dlist_appned(obj->faces, t_dlist_node_new(1));
}

int parse_content(char *s, t_obj_pars *obj)
{

    #define eq(s) !strcmp(token, s)

    if (eq("v")) {
        parse_v(s, obj);
    } else if (eq("vt")) {
        parse_vt(s, obj);
    } else if (eq("vn")) {
        parse_vn(s, obj);
    } else if (eq("f")) {
        populate_f(obj);
    }
    return 1;
}

int parse_file(char *filename, t_obj **obj)
{
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;

    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stderr, "Error opening file '%s'\n", filename);
        return EXIT_FAILURE;
    }
    
    line_size = getline(&line_buf, &line_buf_size, fp);
    while (line_size >= 0)
    {
        line_count++;

        if (SHOW_CONTENT) {
            printf("line[%06d]: chars=%06zd, buf size=%06zu, contents: %s", line_count,
            line_size, line_buf_size, line_buf);
        }
        parse_content(line_buf, obj);
        line_size = getline(&line_buf, &line_buf_size, fp);
    }

    free(line_buf);
    line_buf = NULL;
    fclose(fp);

    return EXIT_SUCCESS;
}

t_obj t_obj_init()
{
    t_obj obj;

    obj.verteces = NULL;
    obj.normales = NULL;
    obj.textures = NULL;
    cvector_push_back(obj.verteces, {0,0,0});
    cvector_push_back(obj.normales, {0,0,0});
    cvector_push_back(obj.textures, {0,0});
    return obj;
}

int main(int ac, char **av)
{
    if (ac < 2) {
        printf("No files provided: pass .obj file as argument\n");
        exit(0);
    }

    t_obj obj = t_obj_init();

    

    if (parse_file(av[1], &obj) == EXIT_FAILURE) {
        exit(0);
    }
    
    return (0);
}