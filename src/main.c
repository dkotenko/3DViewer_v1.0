#include "scop.h"
#include "parser.h"
#include "cvector.h"
#include <stdlib.h>
#include <stdio.h>
#include "s21_matrix.h"




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
    mu_Context ctx;;
    scop.mesh = &mesh;
    scop.g = &g;

    
    init(&scop, filename, &ctx);
    !run(&scop, filename, &ctx);
    exit(0);
    return (0);
}