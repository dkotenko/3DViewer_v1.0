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
    GLUTBackendInit(ac, av);

    if (!GLUTBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, "3DViewer_V1.0")) {
        return 1;
    }

    char *filename = ac > 1 ? av[1] : NULL;    
    t_mesh mesh = {0};

    if(!load_mesh(&mesh, filename)) {
        return (0);
    }

    handle_glut(&mesh);
    
}