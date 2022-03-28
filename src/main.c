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
    t_mesh mesh = t_mesh_init_zeroes();

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