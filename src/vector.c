#include "vector.h"

t_vec2f t_vec2f_new(float x, float y)
{
    t_vec2f v = (t_vec2f){.x = x, .y = y};
    return v;
}

t_vec3f t_vec3f_new(float x, float y, float z)
{
    t_vec3f v = (t_vec3f){.x = x, .y = y, .z = z};
    return v;
}