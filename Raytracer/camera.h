#ifndef CAMERA_H
# define CAMERA_H

#include "structs.h"
#include "vec3.h"
#include "ray.h"

t_camera camera_init(int width, int height);
t_ray camera_get_ray(t_camera *cam, int i, int j);

#endif
