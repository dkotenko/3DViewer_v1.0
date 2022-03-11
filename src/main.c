#include "scop.h"
#include "parser.h"
#include "cvector.h"
#include <stdlib.h>
#include <stdio.h>

t_mesh t_mesh_init()
{
    t_mesh mesh;

    mesh.vertices = NULL;
    mesh.normals = NULL;
    mesh.textures = NULL;
    t_vec3 v3 = {0,0,0};
    t_vec2 v2 = {0,0};
    cvector_push_back(mesh.vertices, v3);
    cvector_push_back(mesh.normals, v3);
    cvector_push_back(mesh.textures, v2);
    return mesh;
}

int main(int ac, char **av)
{
    if (ac < 2) {
        printf("No files provided: pass .obj file as argument\n");
        exit(0);
    }

    t_mesh mesh = t_mesh_init();
    if (parse_file(av[1], &mesh) == EXIT_FAILURE) {
        exit(0);
    }
    printf("%d\n", cvector_size(mesh.faces));
    return (0);
}