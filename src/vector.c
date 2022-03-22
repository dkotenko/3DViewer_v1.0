#include "vector.h"
#include <stdio.h>

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

void t_vec3f_print(t_vec3f v, char *name)
{
    printf("t_vec3f %s: x:%f y:%f z:%f\n", name, v.x, v.y, v.z);
}

t_vec3f t_vec3f_sum(t_vec3f a, t_vec3f b)
{
    t_vec3f new;

    new.x = a.x + b.x;
    new.y = a.y + b.y;
    new.z = a.z + b.z;

    return new;
}

t_vec3f t_vec3f_sub(t_vec3f a, t_vec3f b)
{
    t_vec3f new;

    new.x = a.x - b.x;
    new.y = a.y - b.y;
    new.z = a.z - b.z;

    return new;
}

t_vec3f t_vec3f_multf(t_vec3f a, float f)
{
    t_vec3f new;

    new.x = a.x * f;
    new.y = a.y * f;
    new.z = a.z * f;

    return new;
}

