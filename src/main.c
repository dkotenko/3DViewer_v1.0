#include "scop.h"
#include "parser.h"
#include "cvector.h"
#include <stdlib.h>
#include <stdio.h>
#include "s21_matrix.h"


#define DEBUG 0

#define START_INDEX 0
t_mesh t_mesh_init()
{
    t_mesh mesh = {0};
    t_vec3f v3 = {0}; 
    t_vec2f v2 = {0};
    
    t_face face;

    /*
    ** opengl indices start with 1
    */
    if (START_INDEX) {
        cvector_push_back(mesh.faces, face);
        cvector_push_back(mesh.vertices, v3);
        cvector_push_back(mesh.normals, v3);
        cvector_push_back(mesh.textures, v2);
    }
    return mesh;
}

void print_parse_result(t_mesh *mesh)
{
    if (!DEBUG) {
        return ;
    }
    printf("faces: %d\n", (int)cvector_size(mesh->faces) - 1);
    printf("vertices: %d\n", (int)cvector_size(mesh->vertices) - 1);
    printf("textures: %d\n", (int)cvector_size(mesh->textures) - 1);
    printf("normals: %d\n", (int)cvector_size(mesh->normals) - 1);
}

void draw_mesh(t_mesh *mesh)
{
    return ;
}

void get_default_mesh(t_mesh *mesh)
{
    cvector_push_back(mesh->vertices, t_vec3f_new(-1.0f, -1.0f, 0.5773f));
    cvector_push_back(mesh->vertices, t_vec3f_new(0.0f, -1.0f, -1.15475f));
    cvector_push_back(mesh->vertices, t_vec3f_new(1.0f, -1.0f, 0.5773f));
    cvector_push_back(mesh->vertices, t_vec3f_new(0.0f, 1.0f, 0.0f));
}

int main(int ac, char **av)
{
    /*
    if (ac < 2) {
        printf("No files provided: pass .obj file as argument\n");
        exit(0);
    }
    */
    t_mesh mesh = t_mesh_init();

    if (ac > 1) {
        if (parse_file(av[1], &mesh) == EXIT_FAILURE) {
            printf("parsing error\n");
            exit(0);
        }
        draw_mesh(&mesh);
        print_parse_result(&mesh);
    } else {
        get_default_mesh(&mesh);
    }
    handle_glut(ac, av, &mesh);
    return (0);
}