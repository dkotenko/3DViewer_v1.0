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
#define PATTERN_F_3 "f %d %d %d"
#define PATTERN_F_3_SLASH "f %d/%d/%d %d/%d/%d %d/%d/%d"
#define PATTERN_F_4 "f %d %d %d %d"
#define PATTERN_F_4_SLASH "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d"
#define CVECTOR_LOGARITHMIC_GROWTH

#define is_space(c) c == ' ' || c == '\t'


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
    cvector_push_back(mesh->vertices, new);
}

void parse_vt(char *s, t_mesh *mesh)
{
    t_vec2f new;

    sscanf(s, PATTERN_VT, &new.x, &new.y);
    cvector_push_back(mesh->textures, new);
}

static int	count_words(char const *s)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] && isspace(s[i]))
			i++;
		if (!s[i])
			return (counter);
		counter++;
		while (s[i] && !isspace(s[i]))
			i++;
	}
	return (counter);
}

void parse_f(char *s, t_mesh *mesh)
{
    t_face_transport face;
    t_vertex_index *indices = NULL;
    
    int words_num = count_words(s);
    if (words_num != 4 && words_num != 5) {
        return ;
    }
    if (words_num == 3) {
        indices = (t_vertex_index *)calloc(sizeof(t_vertex_index), 3);
        face.vertex_num = 3;

        if (strchr(s, '/')) {
            sscanf(s, PATTERN_F_3_SLASH, \
        &indices[0].vertex, &indices[0].texture, &indices[0].normal, \
        &indices[1].vertex, &indices[1].texture, &indices[1].normal, \
        &indices[2].vertex, &indices[2].texture, &indices[2].normal);
        } else {
            sscanf(s, PATTERN_F_3, &indices[0].vertex, &indices[1].vertex, &indices[2].vertex);
            indices[0].normal = indices[0].vertex;
            indices[1].normal = indices[1].vertex;
            indices[2].normal = indices[2].vertex;
            indices[0].texture = indices[0].vertex;
            indices[1].texture = indices[1].vertex;
            indices[2].texture = indices[2].vertex;
        }
    } else if (words_num == 4) {
        indices = (t_vertex_index *)calloc(sizeof(t_vertex_index), 4);
        face.vertex_num = 4;
        if (strchr(s, '/')) {
            sscanf(s, PATTERN_F_4_SLASH, \
            &indices[0].vertex, &indices[0].texture, &indices[0].normal, \
            &indices[1].vertex, &indices[1].texture, &indices[1].normal, \
            &indices[2].vertex, &indices[2].texture, &indices[2].normal, \
            &indices[3].vertex, &indices[3].texture, &indices[3].normal);
        } else {
            sscanf(s, PATTERN_F_3, &indices[0].vertex, &indices[1].vertex, &indices[2].vertex, &indices[3].vertex);
            indices[0].normal = indices[0].vertex;
            indices[1].normal = indices[1].vertex;
            indices[2].normal = indices[2].vertex;
            indices[3].normal = indices[3].vertex;
            indices[0].texture = indices[0].vertex;
            indices[1].texture = indices[1].vertex;
            indices[2].texture = indices[2].vertex;
            indices[3].normal = indices[3].vertex;
        }
        
    }
    face.indices = indices;
    cvector_push_back(mesh->faces_transport, face);
}

void populate_f(t_mesh *mesh)
{
    t_face_transport *t = mesh->faces_transport;
    int faces_num = cvector_size(t);
    
    if (!faces_num) {
        return;
    printf("here\n");
    }
    for (int i = 0; i < faces_num; i++) {
        t_face face = {0};
        face.vertex_num = t[i].vertex_num;
        for (int j = 0; j < face.vertex_num; j++) {
            printf("%d %d\n", i, j);
            t_vertex vertex_to_add = {0};

            int vertex_index = t[i].indices[j].vertex;
            vertex_to_add.vertex = mesh->vertices[vertex_index];

            int normal_index = t[i].indices[j].normal;
            vertex_to_add.normal = mesh->normals[normal_index];

            int texture_index = t[i].indices[j].texture;
            vertex_to_add.texture = mesh->textures[texture_index];

            cvector_push_back(face.vertices, vertex_to_add);
        }
        cvector_push_back(mesh->faces, face);
    }
    printf("%d\n", mesh->faces[0].vertices[0].vertex);
}

int parse_content(char *s, t_mesh *mesh)
{
    if (!strncmp("vt", s, 2)) {
        parse_vt(s, mesh);
    } else if (!strncmp("vn", s, 2)) {
        parse_vn(s, mesh);
    } else if (!strncmp("v", s, 1)) {
        parse_v(s, mesh);
    } else if (!strncmp("f", s, 1)) {
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


