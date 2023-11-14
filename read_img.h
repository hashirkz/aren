#ifndef READ_IMG_H
#define READ_IMG_H

#include <SDL2/SDL.h>
#include "ascii.h"

SDL_Surface* stretch_resize(SDL_Surface* img, int new_h, double aspect);
double rgb_2_gray(Uint8 r, Uint8 g, Uint8 b);
img_gray* read_img(char* path, int* h, double* aspect);

#endif