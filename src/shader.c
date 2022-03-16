#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string.h>
#include "scop.h"

extern GLint gTranslationLocation;

static void add_shader(GLuint shader_program, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;

    GLint Lengths[1];
    Lengths[0] = (GLint)strlen(pShaderText);

    glShaderSource(ShaderObj, 1, p, Lengths);

    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(shader_program, ShaderObj);
}

const char* vs_file = "shaders/shader.vs";
const char* fs_file = "shaders/shader.fs";

int compile_shaders()
{
    GLuint shader_program = glCreateProgram();

    if (shader_program == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    char *vs;
    char *fs;

    if (!(vs = read_file((char *)vs_file))) {
        return (1);
    };

    add_shader(shader_program, vs, GL_VERTEX_SHADER);

    if (!(fs = read_file((char *)fs_file))) {
        return (1);
    };

    add_shader(shader_program, fs, GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(shader_program, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        return (1);
    }

    gTranslationLocation = glGetUniformLocation(shader_program, "gTranslation");
    if (gTranslationLocation == -1) {
        printf("Error getting uniform location of 'gTranslation'\n");
        return (1);
    }

    glValidateProgram(shader_program);
    glGetProgramiv(shader_program, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(shader_program, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        return (1);
    }

    glUseProgram(shader_program);
    return (0);
}