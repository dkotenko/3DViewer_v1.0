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
    printf("vertex_indices num: %d\n", t->indices_num);
    for (int i = 0; i < t->indices_num; i++) {
        t_vertex_index_print(t->indices[i]);
    }
    printf("\n");
}

void print_mesh(t_mesh *mesh)
{
    printf("MESH OUTPUT:\n\n");
    printf("vertices num: %d\n", cvector_size(mesh->vertices));
    for (int i = 0; i < cvector_size(mesh->vertices); i++) {
        t_vec3f_print(mesh->vertices[i], "vertex");
    }

    printf("normals num: %d\n", cvector_size(mesh->normals));
    for (int i = 0; i < cvector_size(mesh->normals); i++) {
        t_vec3f_print(mesh->normals[i], "normal");
    }

    printf("textures num: %d\n", cvector_size(mesh->textures));
    for (int i = 0; i < cvector_size(mesh->textures); i++) {
        t_vec2f_print(mesh->textures[i], "texture");
    }

    printf("faces num: %d\n", cvector_size(mesh->faces));
    for (int i = 0; i < cvector_size(mesh->faces); i++) {
        t_face_print(&mesh->faces[i], "face");
    }

    printf("faces transport num: %d\n", cvector_size(mesh->faces_transport));
    for (int i = 0; i < cvector_size(mesh->faces_transport); i++) {
        t_face_transport_print(&mesh->faces_transport[i], "face transport");
    }
}

void t_pipeline_print(t_pipeline *p)
{
    PersProjInfo t = p->m_persProjInfo;
    t_vec3f_print(p->m_scale, "m_scale");
    t_vec3f_print(p->m_worldPos, "m_worldPos");
    t_vec3f_print(p->m_rotateInfo, "m_rotateInfo");

    printf("PersProjInfo: FOV:%f Width:%f Height:%f zNear:%f zFar:%f\n",\
    t.FOV, t.Width, t.Height, t.zNear, t.zFar);

    OrthoProjInfo o = p->m_orthoProjInfo;
    printf("OrthoProjInfo: r:%f l:%f b:%f t:%f n:%f f:%f\n",\
    o.r, o.l, o.b, o.t, o.n, o.f);

    t_camera_print(&p->m_camera);
    s21_print_matrix(&p->m_WVPtransformation, "m_WVPtransformation");
    s21_print_matrix(&p->m_VPtransformation, "m_VPtransformation");
    s21_print_matrix(&p->m_WPtransformation, "m_WPtransformation");
    s21_print_matrix(&p->m_WVtransformation, "m_WVtransformation");
    s21_print_matrix(&p->m_Wtransformation, "m_Wtransformation");
    s21_print_matrix(&p->m_Vtransformation, "m_Vtransformation");
    s21_print_matrix(&p->m_ProjTransformation, "m_ProjTransformation");
}