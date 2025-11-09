#include "ray.h"

t_ray ray_init() {
    t_ray ray;

    ray.origin = vec3_init(0,0,0);
    ray.dir = vec3_init(0,0,0);
    return ray;
}

t_vec3 ray_at(t_ray ray, double t) {
    t_vec3 result;

    result.coor[0] = ray.origin.coor[0] + ray.dir.coor[0] * t;
    result.coor[1] = ray.origin.coor[1] + ray.dir.coor[1] * t;
    result.coor[2] = ray.origin.coor[2] + ray.dir.coor[2] * t;
    return result;
}

t_ray ray_create(t_vec3 origin, t_vec3 dir) {
    t_ray ray;
    
    ray.origin = origin;
    ray.dir = dir;

    return ray;
}

t_vec3 ray_color(t_ray *r) {
    t_vec3 unit_direction = vec3_normalize(r->dir);
    double a = 0.5 * (vec3_get(&unit_direction, 1) + 1.0);
    
    // Interpolación lineal: (1-a)*blanco + a*azul
    t_vec3 white = vec3_init(1.0, 1.0, 1.0);
    t_vec3 blue = vec3_init(0.5, 0.7, 1.0);
    
    t_vec3 color1 = vec3_scale(white, 1.0 - a);
    t_vec3 color2 = vec3_scale(blue, a);
    
    return vec3_sum(color1, color2);
}
