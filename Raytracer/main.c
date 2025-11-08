#include <stdio.h>

int main() {
    int image_width = 300;
    int image_height = 400;
    int image_color = 255;
    
    printf("P3\n");
    printf("%d %d\n", image_width, image_height );
    printf("%d\n", image_color );


    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width ; j++) {
            double r = (double)j / (image_width - 1);
            double g = (double)i / (image_height - 1);
            double b = 0;

            int ir = (int)(255.99 * r);
            int ig = (int)(255.99 * g);
            int ib = (int)(255.99 * b);

            printf("%d %d %d\n", ir, ig, ib);
        }
    }
    return 0;
}
