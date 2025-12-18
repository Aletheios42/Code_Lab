#ifndef SPHERE_H
# define SPHERE_H

#include "structs.h"

#include "vec3.h"
#include "ray.h"

#include <stdbool.h>

bool hit_sphere(t_vec3 center, double radius, t_ray r);

#endif
