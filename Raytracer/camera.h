#ifndef CAMERA_H
# define CAMERA_H

#include "vec3.h"
#include "ray.h"

typedef struct s_camera {
    // Posicion del ojo
    t_vec3 origin;
    // distancia de la proyeccion
    double focal_length;
    // tamaño de la proyeccion
    double viewport_ratio;
    double viewport_width;
    double viewport_height;
    
    t_vec3 viewport_u;
    t_vec3 viewport_v;
    // la mitad del ancho de la medida del pixel
    t_vec3 pixel_delta_u;
    // la mitas del alto de la medida del pixel
    t_vec3 pixel_delta_v;

    // pixel de arriba a la izquierda (por el que recorreremos el viewport)
    t_vec3 viewport_upper_left;
    // centro del primer pixel el de arriba a la izquierda
    t_vec3 pixel00_loc;
} t_camera;

t_camera camera_init(int width, int height);
t_ray camera_get_ray(t_camera *cam, int i, int j);

#endif
