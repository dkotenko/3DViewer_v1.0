#pragma once

typedef struct {
    union {
        float x;
	    float u;
    };

    union {
        float y;
        float v;
    };
} t_vec2f;

typedef struct {
    union {
        float x;
        float r;
    };
    union {
        float y;
        float g;
    };
    union {
        float z;
        float b;
    };} t_vec3f;

t_vec3f t_vec3f_new(float x, float y, float z);
t_vec2f t_vec2f_new(float x, float y);