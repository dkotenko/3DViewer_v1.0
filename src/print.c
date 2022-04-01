#include "scop.h"
#include "cvector.h"

void t_vertex_print(t_vertex vertex)
{
    t_vec3f_print(vertex.vertex, "vertex");
    t_vec3f_print(vertex.normal, "normal");
    t_vec2f_print(vertex.texture, "texture");
    printf("\n");
}

void t_vertex_index_print(t_vertex_index vi)
{
    printf("vertex index: %d | texture index: %d | normal index: %d",\
    vi.vertex, vi.texture, vi.normal);
    printf("\n");
}

void t_face_print(t_face *face, char *label)
{
    printf("%s\n", label);
    printf("vertices num: %d\n", face->vertex_num);
    printf("VB: %d, IB: %d\n", face->VB, face->IB);
    for (int i = 0; i < face->vertex_num; i++) {
        t_vertex_print(face->vertices[i]);
    }
    printf("\n");
}

void t_face_transport_print(t_face_transport *t, char *label)
{
    printf("%s\n", label);
    printf("vertex_indices num: %d\n", t->vertex_num);
    for (int i = 0; i < t->vertex_num; i++) {
        t_vertex_index_print(t->indices[i]);
    }
    printf("\n");
}

void print_mesh(t_mesh *mesh)
{
    printf("MESH OUTPUT:\n\n");
    printf("vertices num: %d\n", cvector_size(mesh->vertices) - START_INDEX);
    for (int i = 0 + START_INDEX; i < cvector_size(mesh->vertices) + START_INDEX; i++) {
        t_vec3f_print(mesh->vertices[i], "vertex");
    }

    printf("normals num: %d\n", cvector_size(mesh->normals) - START_INDEX);
    for (int i = 0  + START_INDEX; i < cvector_size(mesh->normals) + START_INDEX; i++) {
        t_vec3f_print(mesh->normals[i], "normal");
    }

    printf("textures num: %d\n", cvector_size(mesh->textures) - START_INDEX);
    for (int i = 0 + START_INDEX; i < cvector_size(mesh->textures) + START_INDEX; i++) {
        t_vec2f_print(mesh->textures[i], "texture");
    }

    printf("faces num: %d\n", cvector_size(mesh->faces) - START_INDEX);
    for (int i = 0 + START_INDEX; i < cvector_size(mesh->faces) + START_INDEX; i++) {
        t_face_print(mesh->faces, "face");
    }

    printf("faces transport num: %d\n", cvector_size(mesh->faces_transport) - START_INDEX);
    for (int i = 0 + START_INDEX; i < cvector_size(mesh->faces_transport) + START_INDEX; i++) {
        t_face_transport_print(mesh->faces_transport, "face transport");
    }
}