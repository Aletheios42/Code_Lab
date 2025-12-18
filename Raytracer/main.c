#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "sphere.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void write_color(FILE *out, t_vec3 pixel_color) {
    double r = vec3_get(&pixel_color, 0);
    double g = vec3_get(&pixel_color, 1);
    double b = vec3_get(&pixel_color, 2);

    int ir = (int)(255.99 * r);
    int ig = (int)(255.99 * g);
    int ib = (int)(255.99 * b);

    fprintf(out, "%d %d %d\n", ir, ig, ib);
}

t_image recompila_datos() {

    t_image params;
    char input[200];
    printf("Introduce el ancho de la imagen\n");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        params.width = atoi(input);
    }
    printf("Introduce el alto de la imagen\n");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        params.height = atoi(input);
    }
    printf("Introduce el color maximo de la imagen\n");
    if (fgets(input, sizeof(input), stdin) != NULL){
        params.color = atoi(input);
    }
    printf("Introduce el nombre del archivo en el que se guardara la imagen\n");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        params.outfile = fopen(input, "w");
    }
    return params;
}

int main() {
    t_image image;
    image = recompila_datos();

    t_camera cam;
    cam = camera_init(image.width, image.height);

    fprintf(image.outfile, "P3\n");
    fprintf(image.outfile, "%d %d\n", image.width, image.height );
    // para el formato ppm
    fprintf(image.outfile, "%d\n", image.color);


    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width ; j++) {
          t_ray r = camera_get_ray(&cam, i, j);
            t_vec3 pixel_color = ray_color(&r);
            write_color(image.outfile, pixel_color);
        }
    }
    return 0;
}
