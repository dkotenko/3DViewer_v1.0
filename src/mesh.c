#include "scop.h"
#include "cvector.h"
#include "parser.h"
#include <GL/glew.h>
#include <GL/freeglut.h>


t_mesh t_mesh_init_zeroes()
{
    t_mesh mesh = {0};
    t_vec3f v3 = {0}; 
    t_vec2f v2 = {0};
    t_face face = {0};
    t_face_transport t = {0};

    /*
    ** opengl indices start with 1
    */
    if (START_INDEX) {
        cvector_push_back(mesh.faces_transport, t);
        cvector_push_back(mesh.faces, face);
        cvector_push_back(mesh.vertices, v3);
        cvector_push_back(mesh.normals, v3);
        cvector_push_back(mesh.textures, v2);
    }
    return mesh;
}



void draw_mesh(t_mesh *mesh)
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    t_face *m_Entries = mesh->faces;
    int faces_num = cvector_size(mesh->faces);

    for (unsigned int i = 0 ; i < faces_num ; i++) {
        glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (const GLvoid*)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (const GLvoid*)20);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

        /*
        const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;
        if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]) {
            m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
        }
        */

        glDrawElements(GL_TRIANGLES, m_Entries[i].vertex_num, GL_UNSIGNED_INT, 0);
    }

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
    cvector_push_back(mesh->vertices, t_vec3f_new(0.0f, 1.0f, 0.0f));
    unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               0, 1, 2 };

    for (int i = 0 + START_INDEX; i < 4 + START_INDEX; i++) {
        t_face_transport t = {0};

        for (int j = 0; j < 3; j++) {
            t_vertex_index index = {0};
            index.vertex = Indices[(START_INDEX ? i - 1 : i) + j];
            cvector_push_back(t.indices, index);
        }
        t.vertex_num = 3;
        cvector_push_back(mesh->faces_transport, t);
    }
    t_face_transport_print(mesh->faces_transport, "");
    exit(0);
    populate_f(mesh);
}


