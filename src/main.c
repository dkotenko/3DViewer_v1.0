#include "scop.h"
#include "parser.h"
#include "cvector.h"
#include <stdlib.h>
#include <stdio.h>

#define DEBUG 0

t_mesh t_mesh_init()
{
    t_mesh mesh;

    memset(&mesh, 0, sizeof(t_mesh));
    t_vec3 v3 = {0,0,0};
    t_vec2 v2 = {0,0};
    t_face face;
    cvector_push_back(mesh.faces, face);
    cvector_push_back(mesh.vertices, v3);
    cvector_push_back(mesh.normals, v3);
    cvector_push_back(mesh.textures, v2);
    return mesh;
}

void print_parse_result()
{
    if (!DEBUG) {
        return ;
    }
    printf("faces: %d\n", cvector_size(mesh.faces) - 1);
    printf("vertices: %d\n", cvector_size(mesh.vertices) - 1);
    printf("textures: %d\n", cvector_size(mesh.textures) - 1);
    printf("normals: %d\n", cvector_size(mesh.normals) - 1);
}

void draw_mesh(t_mesh *mesh)
{
    return ;
}

int main(int ac, char **av)
{
    if (ac < 2) {
        printf("No files provided: pass .obj file as argument\n");
        exit(0);
    }

    t_mesh mesh = t_mesh_init();
    if (parse_file(av[1], &mesh) == EXIT_FAILURE) {
        printf("parsing error\n");
        exit(0);
    }
    draw_mesh(&mesh);
    print_parse_result();
    return (0);
}