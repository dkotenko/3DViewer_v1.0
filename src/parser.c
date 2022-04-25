#define  _POSIX_C_SOURCE 200809L

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
#define skip_spaces(s) while (*s && isspace(*s)) {s++;}
#define skip_non_spaces(s) while (*s && !isspace(*s)) {s++;}

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
    t_face_transport face = {0};
    
    s += 2; //skip "f ";
    int words_num = count_words(s);
    if (words_num < 3) {
        printf("invalid line, must be at least 3 verices: %s\n", s);
        return ;
    }
    
    
    bool is_slashed = strchr(s, '/');
    while (*s) {
        t_vertex_index index = {0};
        memset(&index, -1, sizeof(t_vertex_index));

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
    
    if (words_num == 3) {
        cvector_push_back(mesh->faces_transport, face);
    } else {
        t_face_transport *faces = split_face(&face);
        for (long unsigned int i = 0; i < cvector_size(faces); i++) {
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
            int vertex_index = t[i].indices[j].vertex - 1;
            
            if (vertex_index != NO_ELEMENT) {
                vertex_to_add.vertex = mesh->vertices[vertex_index];
            } else {
                vertex_to_add.vertex = t_vec3f_new(i, j, j);
            }
            
            int normal_index = t[i].indices[j].normal - 1;
            if (normal_index != NO_ELEMENT && (is_nor)) {
                vertex_to_add.normal = mesh->normals[normal_index];
            } else {
                vertex_to_add.normal = Normalize(vertex_to_add.vertex);
            }
            int texture_index = t[i].indices[j].texture - 1;
            if (texture_index != NO_ELEMENT && (is_tex)) {
                vertex_to_add.texture = mesh->textures[texture_index];
            } else {
                vertex_to_add.texture.x = vertex_to_add.normal.x;
                vertex_to_add.texture.y = vertex_to_add.normal.y;
            }
            cvector_push_back(mesh->all_vertices, vertex_to_add.vertex);
            cvector_push_back(mesh->all_textures, vertex_to_add.texture);
            cvector_push_back(mesh->all_normals, vertex_to_add.normal);
            cvector_push_back(face.vertices, vertex_to_add);
            cvector_push_back(mesh->vertices_to_draw, vertex_to_add);
            cvector_push_back(mesh->indices_to_draw, t[i].indices[j].vertex);
            //cvector_push_back(mesh->indices_to_draw, t[i].indices[j].texture);
            //cvector_push_back(mesh->indices_to_draw, t[i].indices[j].normal);

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
    populate_f(mesh);
    return EXIT_SUCCESS;
}

void print_parse_result(t_scop *scop)
{
    if (!scop->config->debug) {
        return ;
    }

    t_mesh *mesh = scop->mesh;
    printf("faces: %d\n", (int)cvector_size(mesh->faces) - 1);
    printf("vertices: %d\n", (int)cvector_size(mesh->vertices) - 1);
    printf("textures: %d\n", (int)cvector_size(mesh->textures) - 1);
    printf("normals: %d\n", (int)cvector_size(mesh->normals) - 1);
}

int len_s;

static int startswith(char *s, char *pattern)
{
	int len_p = strlen(pattern);

	if (len_p > len_s) {
		return 0;
	}
	return !strncmp(s, pattern, len_s);
}

static void parse_int(char *s, int *value) {
    skip_non_spaces(s);
    skip_spaces(s);
    if (!*s) {
        return;
    }
    *value = atoi(s);
}

static void parse_string(char *s, char **value) {
    skip_non_spaces(s);
    skip_spaces(s);
    if (!*s) {
        return;
    }
    if (*value) {
        free(*value);
    }
    *value = ft_strdup(s);
}

void parse_config_content(char *s, t_config *config)
{
	len_s = strlen(s);

	if (startswith(s, "window_width")) {
        parse_int(s, &config->window_width);
	} else if (startswith(s, "window_height")) {
        parse_int(s, &config->window_height);
	} else if (startswith(s, "debug")) {
        parse_int(s, &config->debug);
	} else if (startswith(s, "window_start_x")) {
        parse_int(s, &config->window_start_x);
	} else if (startswith(s, "window_start_y")) {
        parse_int(s, &config->window_start_y);
	} else if (startswith(s, "app_name")) {
        parse_string(s, &config->app_name);
	}
}

int parse_config_file(t_config *config)
{
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;

    FILE *fp = fopen(CFG_FILENAME, "r");
    if (!fp)
    {
        fprintf(stderr, "Error opening file '%s'\n", CFG_FILENAME);
        return EXIT_FAILURE;
    }
    
    line_size = getline(&line_buf, &line_buf_size, fp);
    while (line_size >= 0)
    {
        line_count++;
        parse_config_content(line_buf, config);
        free(line_buf);
        line_buf = NULL;
        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    if (line_buf) {
        free(line_buf);
    }
    line_buf = NULL;
    fclose(fp);
    return 0;
}

#include "scop.h"
#include <stdio.h>
#include <stdlib.h>

char *read_file(char *filename)
{
	FILE *fp;
	long lSize;
	char *buffer;

	fp = fopen (filename, "rb");
	if( !fp ) {
		perror(filename);
		return(0);
	} 

	fseek( fp , 0L , SEEK_END);
	lSize = ftell( fp );
	rewind( fp );

	buffer = calloc( 1, lSize+1 );
	if( !buffer ) {
		fclose(fp);
		fputs("read_file: memory alloc fails",stderr);
		return(0);
	} 

	/* copy the file into the buffer */
	if(1 != fread( buffer , lSize, 1 , fp)) {
		fclose(fp);
		free(buffer);
		fputs("read_file: entire read fails",stderr);
		return(0);
	}
	fclose(fp);
	return buffer;
}
