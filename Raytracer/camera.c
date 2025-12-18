#include "camera.h"

t_camera camera_init(int image_width, int image_height) {
    t_camera cam; 
    
    cam.origin = vec3_init(0,0,0);
    cam.focal_length = 1;
    cam.viewport_ratio = 1.0 / 1.0;
    cam.viewport_height = 1.0;
    cam.viewport_width = cam.viewport_height / cam.viewport_ratio;

    // Crear los vectores de la ventana
    cam.viewport_u = vec3_init(cam.viewport_width, 0, 0);
    cam.viewport_v = vec3_init(0, -cam.viewport_height, 0);

    cam.pixel_delta_u = vec3_scale(cam.viewport_u, 1.0 / image_width);
    cam.pixel_delta_v = vec3_scale(cam.viewport_v, 1.0 / image_height);

    // calcular Upper-Left en el grid
    t_vec3 focal_offset = vec3_init(0, 0, cam.focal_length);
    cam.viewport_upper_left = vec3_subtract(cam.origin, focal_offset);
    cam.viewport_upper_left = vec3_subtract(cam.viewport_upper_left, vec3_scale(cam.viewport_u, 0.5));
    cam.viewport_upper_left = vec3_subtract(cam.viewport_upper_left, vec3_scale(cam.viewport_v, 0.5));

    // calcular el pixel en la celda del grid
    t_vec3 half_pixel = vec3_scale(vec3_sum(cam.pixel_delta_u, cam.pixel_delta_v), 0.5);
    cam.pixel00_loc = vec3_sum(cam.viewport_upper_left, half_pixel);
    return cam;
}

t_ray camera_get_ray(t_camera *cam, int i, int j) {
    // Calcular centro del pixel (i, j)
    t_vec3 offset_u = vec3_scale(cam->pixel_delta_u, i);
    t_vec3 offset_v = vec3_scale(cam->pixel_delta_v, j);
    t_vec3 pixel_center = vec3_sum(cam->pixel00_loc, vec3_sum(offset_u, offset_v));
    
    // Dirección del rayo
    t_vec3 ray_direction = vec3_subtract(pixel_center, cam->origin);
    
    return ray_create(cam->origin, ray_direction);
}
