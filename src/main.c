#include "scop.h"
#include "parser.h"
#include "cvector.h"
#include <stdlib.h>
#include <stdio.h>
#include "s21_matrix.h"


t_config *g_config;

int main(int ac, char **av)
{
    /*
    if (ac < 2) {
        printf("No files provided: pass .obj file as argument\n");
        exit(0);
    }
    */
    char *filename = ac > 1 ? av[1] : NULL;    
    
    t_scop scop = {0};
    t_mesh mesh = {0};
    t_globals g = {0};
    t_config c = {0};
    scop.mesh = &mesh;
    scop.g = &g;
    scop.config = &c;
    g.texture_filename = ft_strdup("resources/texture.jpg");
    g_config = &c;
    
    init(&scop, filename);
    if (!run(&scop)) {
        printf("error during running, abort\n");
    }
    
    exit(0);
    return (0);
}