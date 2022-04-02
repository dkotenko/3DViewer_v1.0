#include "scop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cvector.h"
#include "parser.h"

#define SHOW_CONTENT 0
#define DELIM ' '

#define PATTERN_V "v %f %f %f"
#define PATTERN_VN "vn %f %f %f"
#define PATTERN_VT "vt %f %f"
#define PATTERN_F "%d"
#define PATTERN_F_SLASH "%d/%d/%d"
#define PATTERN_F_3 "f %d %d %d"
#define PATTERN_F_3_SLASH "f %d/%d/%d %d/%d/%d %d/%d/%d"
#define PATTERN_F_4 "f %d %d %d %d"
#define PATTERN_F_4_SLASH "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d"
#define CVECTOR_LOGARITHMIC_GROWTH

#define is_space(c) c == ' ' || c == '\t'

#define NO_ELEMENT -1
/*
void skip_first(char *s, char **to_set)
{
    while (*s && !isspace(*s)) {
        s++;
    }
    while (*s && isspace(*s)) {
        s++;
    }
    *to_set = s;
}
*/

void parse_v(char *s, t_mesh *mesh)
{
    t_vec3f new;

    sscanf(s, PATTERN_V, &new.x, &new.y, &new.z);
    cvector_push_back(mesh->vertices, new);
}

void parse_vn(char *s, t_mesh *mesh)
{
    t_vec3f new;

    sscanf(s, PATTERN_VN, &new.x, &new.y, &new.z);
    cvector_push_back(mesh->normals, new);
}

void parse_vt(char *s, t_mesh *mesh)
{
    t_vec2f new;

    sscanf(s, PATTERN_VT, &new.x, &new.y);
    cvector_push_back(mesh->textures, new);
}

#define skip_spaces(s) while (*s && isspace(*s)) {*s++;}
#define skip_non_spaces(s) while (*s && !isspace(*s)) {*s++;}

static int	count_words(char const *s)
{
	int		counter;

	counter = 0;
	while (*s)
	{
        skip_spaces(s);
		if (!*s)
			return (counter);
		counter++;
        skip_non_spaces(s);
	}
	return (counter);
}



//assume all polygons are convex

//USED METHOD: FAN
t_face_transport *split_face(t_face_transport *face)
{
    t_face_transport *faces = NULL;
    int first = 0;
    int second = 1;
    int third = 2;

    for (int i = 0; i < face->indices_num - 2; i++) {
        t_face_transport temp = {0};
        temp.indices_num = 3;
        cvector_push_back(temp.indices, face->indices[first]);
        cvector_push_back(temp.indices, face->indices[second]);
        cvector_push_back(temp.indices, face->indices[third]);
        cvector_push_back(faces, temp);
        second++;
        third++;
    }
    return faces;
}


void parse_f(char *s, t_mesh *mesh)
{
    t_face_transport face;
    
    s += 2; //skip "f ";
    int words_num = count_words(s);
    
    if (words_num < 3) {
        printf("invalid line, must be at least 3 verices: %s\n", s);
        return ;
    }

    bool is_slashed = strchr(s, '/');
    while (*s) {
        t_vertex_index index;
        memset(&index, -1, sizeof(t_vertex_index));
        face.indices_num = 0;

        if (is_slashed) {
            sscanf(s, PATTERN_F_SLASH, &index.vertex, &index.texture, &index.normal);
        } else {
            sscanf(s, PATTERN_F, &index.vertex);
        }
        cvector_push_back(face.indices, index);
        face.indices_num++;
        skip_non_spaces(s);
        skip_spaces(s);
    }
    cvector_push_back(mesh->faces_transport, face);
    
    if (words_num == 3) {
        cvector_push_back(mesh->faces_transport, face);
    } else {
        t_face_transport *faces = split_face(&face);
        for (int i = 0; i < cvector_size(faces); i++) {
            cvector_push_back(mesh->faces_transport, faces[i]);
        }
    }
}

void populate_f(t_mesh *mesh)
{
    t_face_transport *t = mesh->faces_transport;
    int faces_num = cvector_size(t);
    
    if (!faces_num) {
        return;
    }
    
    
    int is_tex = cvector_size(mesh->textures);
    
    int is_nor = cvector_size(mesh->normals);
    for (int i = 0; i < faces_num; i++) {
        t_face face = {0};
        face.vertex_num = t[i].indices_num;
        
        for (int j = 0; j < face.vertex_num; j++) {

            t_vertex vertex_to_add = {0};
            int vertex_index = t[i].indices[j].vertex;
            
            if (vertex_index != NO_ELEMENT) {
                vertex_to_add.vertex = mesh->vertices[vertex_index];
            }
            
            int normal_index = t[i].indices[j].normal;
            if (normal_index != NO_ELEMENT && (is_nor)) {
                vertex_to_add.normal = mesh->normals[normal_index];
            }
            int texture_index = t[i].indices[j].texture;
            if (texture_index != NO_ELEMENT && (is_tex)) {
                vertex_to_add.texture = mesh->textures[texture_index];
            }
            cvector_push_back(face.vertices, vertex_to_add);
        }
        cvector_push_back(mesh->faces, face);
    }
}

int parse_content(char *s, t_mesh *mesh)
{
    if (!strncmp("vt ", s, 3)) {
        parse_vt(s, mesh);
    } else if (!strncmp("vn ", s, 3)) {
        parse_vn(s, mesh);
    } else if (!strncmp("v ", s, 2)) {
        parse_v(s, mesh);
    } else if (!strncmp("f ", s, 2)) {
        parse_f(s, mesh);
    }
    return 1;
}

int parse_file(char *filename, t_mesh *mesh)
{
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;

    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stderr, "Error opening file '%s'\n", filename);
        return EXIT_FAILURE;
    }
    
    line_size = getline(&line_buf, &line_buf_size, fp);
    while (line_size >= 0)
    {
        line_count++;

        if (SHOW_CONTENT) {
            printf("line[%06d]: chars=%06zd, buf size=%06zu, contents: %s", line_count,
            line_size, line_buf_size, line_buf);
        }
        parse_content(line_buf, mesh);
        free(line_buf);
        line_buf = NULL;
        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    if (line_buf) {
        free(line_buf);
    }
    line_buf = NULL;
    fclose(fp);
    for (int i = 0; i < cvector_size(mesh->faces_transport); i++) {
        printf("%d\n", cvector_size(mesh->faces_transport));
    }
    exit(0);
    populate_f(mesh);
    return EXIT_SUCCESS;
}

void print_parse_result(t_mesh *mesh)
{
    if (!DEBUG) {
        return ;
    }
    printf("faces: %d\n", (int)cvector_size(mesh->faces) - 1);
    printf("vertices: %d\n", (int)cvector_size(mesh->vertices) - 1);
    printf("textures: %d\n", (int)cvector_size(mesh->textures) - 1);
    printf("normals: %d\n", (int)cvector_size(mesh->normals) - 1);
}


