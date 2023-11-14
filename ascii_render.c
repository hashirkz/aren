#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ascii.h"
#include "read_img.h"

int main(int argc, char** argv) {

    // printf("%d", argc);
    // invalid arguments
    if (argc < 4) {
        fprintf(stderr, "ERROR: usage ./app <path to img> height stretch_w");
        exit(1);
    }

    else if (argc == 4) {

        char* path = argv[1];
        int h = atoi(argv[2]);
        double aspect = atof(argv[3]);
        img_gray* img = read_img(path, &h, &aspect);

        char* repr = img_gray_to_txt(img, NULL);
        printf("%s", repr);

        free_img_gray(img);
        return 0;
    }

    else if (argc == 5) {
        
        char* path = argv[1];
        int h = atoi(argv[2]);
        double aspect = atof(argv[3]);
        char* ch_set = argv[4];
        img_gray* img = read_img(path, &h, &aspect);

        char* repr = img_gray_to_txt(img, ch_set);
        printf("%s", repr);

        free_img_gray(img);
        return 0;
    }
}