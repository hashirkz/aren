#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ascii.h"

// converts rgb px to grayscale px
double rgb_2_gray(Uint8 r, Uint8 g, Uint8 b) {
    return 0.2126 * r + 0.7152 * g + 0.0722 * b;
}

SDL_Surface* stretch_resize(SDL_Surface* img, int new_h, double aspect) {
    // Calculate the new width to preserve aspect ratio
    int new_w = (int)((double)img->w / img->h * new_h);

    // Create a new surface with the calculated width and img height
    SDL_Surface* stretched = SDL_CreateRGBSurface(0, new_w, new_h, 32, 0, 0, 0, 0);

    // Scale the loaded image to the new surface, preserving aspect ratio
    SDL_BlitScaled(img, NULL, stretched, NULL);

    // Create another surface for horizontal stretching
    SDL_Surface* stretched_horizontal = SDL_CreateRGBSurface(0, new_w * aspect, new_h, 32, 0, 0, 0, 0);

    // Stretch the image horizontally
    SDL_Rect dstRect = {0, 0, (int)(new_w * aspect), new_h};
    SDL_BlitScaled(stretched, NULL, stretched_horizontal, &dstRect);

    // Free the original stretched surface
    SDL_FreeSurface(stretched);

    return stretched_horizontal;
}



img_gray* read_img(char* path, int* h, double* aspect) {
    img_gray* img = (img_gray*)malloc(sizeof(img_gray));

    // sdl init
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "ERROR: sdl init failed: %s\n", SDL_GetError());
        exit(1);
    }

    // more setup not sure what this does
    if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG)) {
        fprintf(stderr, "IMG_Init Error: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }

    // more setup not sure what this does
    SDL_Surface* img_sdl = IMG_Load(path);
    if (!img_sdl) {
        fprintf(stderr, "IMG_Load Error: %s\n", IMG_GetError());
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    if (!h) { *h = img_sdl->h; }
    img_sdl = stretch_resize(img_sdl, *h, *aspect);

    // memory for pxs
    double** pxs = (double**)malloc(sizeof(double*) * img_sdl->h);
    for (int row = 0; row < img_sdl->h; row++) {
        pxs[row] = (double*)malloc(sizeof(double) * img_sdl->w);
    }

    // store grayscale px values into pxs
    for (int row = 0; row < img_sdl->h; ++row) {
        for (int col = 0; col < img_sdl->w; ++col) {
            Uint32 pixel = *(Uint32*)((Uint8*)img_sdl->pixels + img_sdl->pitch * row + col * img_sdl->format->BytesPerPixel);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, img_sdl->format, &r, &g, &b);

            // normalized grayscale px
            pxs[row][col] = rgb_2_gray(r, g, b) / 255.0;
        }
    }

    // assign img_gray all its attributes
    img->h = img_sdl->h;
    img->w = img_sdl->w;
    img->pxs = pxs;

    // end sdl processes and free sdl
    SDL_FreeSurface(img_sdl);
    IMG_Quit();
    SDL_Quit();

    return img;
}
