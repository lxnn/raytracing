#include <stdio.h>

int main() {
    int image_width = 256;
    int image_height = 256;

    printf("P3\n");
    printf("%d %d\n", image_width, image_height);
    printf("%d\n", 255);

    for (int j = 0; j < image_height; j++) {
        fprintf(stderr, "\rProgress: line %d/%d", j, image_height);
        fflush(stderr);
        for (int i = 0; i < image_width; i++) {
            double r = (double) i / image_width;
            double g = (double) j / image_height;
            double b = 0.0;
            printf("%d %d %d ", (int) (255 * r), (int) (255 * g), (int) (255 * b));
        }
        printf("\n");
    }
    fprintf(stderr, "\n");
}
