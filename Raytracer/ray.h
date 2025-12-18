#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "structs.h"

t_ray ray_init();
t_vec3 ray_at(t_ray ray, double t);
t_ray ray_create(t_vec3 origin, t_vec3 dir);
t_vec3 ray_color(t_ray *r);

#endif
