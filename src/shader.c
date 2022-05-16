#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "scop.h"

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

    GLint Success_returned;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &Success_returned);

    if (!Success_returned) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(shader_program, ShaderObj);
}

int compile_shaders(t_globals *g)
{
    GLuint shader_program = glCreateProgram();

    if (shader_program == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    const char* vs_file = "shaders/shader.vs";
    const char* fs_file = "shaders/shader.fs";

    char *vs;
    char *fs;

    if (!(vs = read_file((char *)vs_file))) {
        return (1);
    };

    if (!(fs = read_file((char *)fs_file))) {
        return (1);
    };
    add_shader(shader_program, vs, GL_VERTEX_SHADER);
    add_shader(shader_program, fs, GL_FRAGMENT_SHADER);
    GLint Success_returned = 0;
    GLchar ErrorLog[1024] = { 0 };
    
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &Success_returned);
    if (Success_returned == 0) {
        glGetProgramInfoLog(shader_program, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        return (1);
    }
    
    glValidateProgram(shader_program);
    glGetProgramiv(shader_program, GL_VALIDATE_STATUS, &Success_returned);
    if (!Success_returned) {
        glGetProgramInfoLog(shader_program, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        return (1);
    }


    glUseProgram(shader_program);
    g->shader_program = shader_program;
    g->gWVPLocation = glGetUniformLocation(shader_program, "gWVP");
    assert(g->gWVPLocation != 0xFFFFFFFF);
    g->gSampler = glGetUniformLocation(shader_program, "gSampler");
    assert(g->gSampler != 0xFFFFFFFF);
    return (0);
}