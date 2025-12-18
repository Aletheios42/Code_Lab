#ifndef STRUCT_H
# define STRUCT_H

#include <stdio.h>

typedef struct s_vec3 {
    double coor[3];
} t_vec3;

typedef struct s_ray {
    t_vec3 origin;
    t_vec3 dir;
} t_ray;

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

typedef struct s_image {
    int width;
    int height;
    int color;
    FILE *outfile;
} t_image;

#endif
