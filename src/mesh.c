#include "scop.h"
#include "cvector.h"
#include "parser.h"

#define _free(a) if (a) free(a);


void clear_mesh(t_mesh *mesh)
{
    for (long unsigned int i = 0; i < cvector_size(mesh->faces); i++) {
        _free(mesh->faces_transport[i].indices);
        _free(mesh->faces[i].vertices);
    }

    _free(mesh->faces);
    _free(mesh->faces_transport);
    _free(mesh->vertices);
    _free(mesh->normals);
    _free(mesh->textures);
    memset(mesh, 0, sizeof(t_mesh));
}

void draw_mesh(t_scop *scop)
{
    t_mesh *mesh = scop->mesh;
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->VB);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (const GLvoid*)12);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (const GLvoid*)20);
    
    t_texture_bind(mesh->texture, GL_TEXTURE0);
    
    glDrawArrays(GL_TRIANGLES, 0, cvector_size(mesh->vertices_to_draw));
    //glDrawElements(GL_TRIANGLES, cvector_size(mesh->vertices), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    return ;
}

void get_default_mesh(t_mesh *mesh)
{
    
    cvector_push_back(mesh->vertices, t_vec3f_new(-1.0f, -1.0f, 0.5773f));
    cvector_push_back(mesh->vertices, t_vec3f_new(0.0f, -1.0f, -1.15475f));
    cvector_push_back(mesh->vertices, t_vec3f_new(1.0f, -1.0f, 0.5773f));
    cvector_push_back(mesh->vertices, t_vec3f_new(0.0f, 0.0f, 0.0f));
    //cvector_push_back(mesh->vertices, t_vec3f_new(0.0f, 1.0f, 0.0f));
    unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               0, 1, 2 };

    for (int i = 0; i < 4; i++) {
        t_face_transport t = {0};

        for (int j = 0; j < 3; j++) {
            t_vertex_index index = {0};
            index.vertex = Indices[i + j];
            cvector_push_back(t.indices, index);
        }
        t.indices_num = 3;
        cvector_push_back(mesh->faces_transport, t);
    }
    populate_f(mesh);
}



bool load_mesh(t_mesh *mesh, char *filename)
{
    clear_mesh(mesh);

    if (filename) {
        if (parse_file(filename, mesh) == EXIT_FAILURE) {
            printf("parsing error\n");
            return false;
        }
        //print_parse_result(&mesh);
    } else {
        get_default_mesh(mesh);
    }
    
    return true;
}


