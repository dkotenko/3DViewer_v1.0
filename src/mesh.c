#include "scop.h"
#include "cvector.h"
#include "parser.h"

#define _free(a) if (a) free(a); a = NULL;
#define POSITION_LOCATION  0
#define TEX_COORD_LOCATION 1
#define NORMAL_LOCATION    2

void clear_mesh(t_mesh *mesh)
{
    for (long unsigned int i = 0; i < cvector_size(mesh->faces); i++) {
        _free(mesh->faces_transport[i].indices);
        _free(mesh->faces[i].vertices);
    }
    if (mesh->buffers) {
        glDeleteBuffers(BUFFERS_SIZE_IN_ELEMENTS, mesh->buffers);
    }

    if (mesh->VAO != 0) {
        glDeleteVertexArrays(1, &mesh->VAO);
        mesh->VAO = 0;
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

    glUseProgram (scop->g->shader_program);
    glBindVertexArray(mesh->VAO);

    if (scop->g->shader_program == 0 || mesh->VAO == 0) {
        printf("Drawind error: shader_program id = %d, VAO id = %d",\
        scop->g->shader_program, mesh->VAO );
        return;
    }
    glDrawArrays(GL_TRIANGLES, 0, cvector_size(mesh->vertices_to_draw));
    //glDrawArrays (GL_TRIANGLES, 0, 3);
    /*
    glDrawElementsBaseVertex(GL_TRIANGLES,
                                 cvector_size(mesh->indices_to_draw),
                                 GL_UNSIGNED_INT,
                                 (void*)(sizeof(unsigned int) * 1),
                                 0);
    */
    //printf("%ld\n", cvector_size(mesh->indices_to_draw));
    //glDrawElements( GL_TRIANGLES, cvector_size(mesh->indices_to_draw), GL_UNSIGNED_INT, 1 );
    //glDrawArrays(GL_TRIANGLES, 0, 12);
    glBindVertexArray(0);
    glUseProgram (0);
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

void populate_buffers(t_mesh *mesh)
{
    GLuint *m_Buffers = mesh->buffers;
        
    
    
    t_vec3f *v = mesh->all_vertices;
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[POS_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v[0]) * cvector_size(v), &v[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_LOCATION);
    glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    
    t_vec2f *m_TexCoords = mesh->all_textures;
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_TexCoords[0]) * cvector_size(m_TexCoords), &m_TexCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(TEX_COORD_LOCATION);
    glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

    /*
    
    t_vec3f *m_Normals = mesh->all_normals;
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_Normals[0]) * cvector_size(m_Normals), &m_Normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(NORMAL_LOCATION);
    glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    unsigned int *m_Indices = mesh->indices_to_draw;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices[0]) * cvector_size(m_Indices), &m_Indices[0], GL_STATIC_DRAW);
    */
}

bool load_mesh(t_mesh *mesh, char *filename)
{
    //clear_mesh(mesh); TODO
    
    if (filename == NULL) {
        if (parse_file(filename, mesh) == EXIT_FAILURE) {
            printf("%s: parsing error\n", filename ? "basic mesh" : filename);
            return false;
        }
        //print_parse_result(&mesh);
    } else {
        get_default_mesh(mesh);
    }
    
    
    glGenVertexArrays(1, &mesh->VAO);
    glBindVertexArray(mesh->VAO);
        
    glGenBuffers(BUFFERS_SIZE_IN_ELEMENTS, mesh->buffers);
    populate_buffers(mesh);
    glBindVertexArray(0);


    return true;
}


