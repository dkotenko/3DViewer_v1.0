#include "scop.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

t_texture *t_texture_new(GLenum type, char *filename)
{
    t_texture *t = calloc(1, sizeof(t_texture));
    t->filename = filename;
    t->type = type;

    return t;
}

void t_texture_load(t_texture *t)
{
    stbi_set_flip_vertically_on_load(1);
    unsigned char* image_data = stbi_load(t->filename, &t->width, &t->height, &t->bpp, 0);

    if (!image_data) {
        printf("Can't load texture from '%s' - %s\n", t->filename, stbi_failure_reason());
        exit(0);
    }

    //printf("Width %d, height %d, bpp %d\n", t->width, t->height, t->bpp);

    glGenTextures(1, &t->obj);
    glBindTexture(t->type, t->obj);

    if (t->type == GL_TEXTURE_2D) {
        switch (t->bpp) {
        
        case 1:
            glTexImage2D(t->type, 0, GL_RED, t->width, t->height, 0, GL_RED, GL_UNSIGNED_BYTE, image_data);
            break;

        case 3:
            glTexImage2D(t->type, 0, GL_RGB, t->width, t->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
            break;

        case 4:
            glTexImage2D(t->type, 0, GL_RGBA, t->width, t->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
            break;
        }
    } else {
        printf("Support for texture target %x is not implemented\n", t->type);
        exit(1);
    }
    glTexParameterf(t->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(t->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(t->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(t->type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(t->type, 0);
    stbi_image_free(image_data);
}

void t_texture_bind(t_texture *t, GLenum type)
{
    glActiveTexture(type);
    glBindTexture(t->type, t->obj);
}