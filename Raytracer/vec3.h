#ifndef VEC3_H
#define VEC3_H

#include "structs.h"
#include <math.h>

t_vec3 vec3_init(double x, double y, double z);
double vec3_get(t_vec3 *v, int index);
t_vec3 vec3_sum(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_subtract(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_multuply(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_divide(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_scale(t_vec3 v1, double scalar);
t_vec3 vec3_divide_scalar(t_vec3 v1, double scalar);
double vec3_lenght(t_vec3 v);
double vec3_lenght_squared(t_vec3 v);
t_vec3 vec3_normalize(t_vec3 v);
double vec3_dot(t_vec3 v1, t_vec3 v2);
#endif
