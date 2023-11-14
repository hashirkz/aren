#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "ascii.h"

// ascii characters from 0-100 brightness
char* ASCII_CH =  " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

img_gray* create_img_gray(int h, int w, double num) {
    img_gray* img;
    double** pxs;

    // memeory for img and 2d pxs tensor
    img = (img_gray*)malloc(sizeof(img_gray));
    pxs = (double**)malloc(sizeof(double*) * h);

    for(int row=0; row < h; row++) {
        // memory for each row
        pxs[row] = (double*)malloc(sizeof(double) * w);

        for (int col=0; col < w; col++) {
            pxs[row][col] = num;
        }
    }

    // assign img values
    img->h = h;
    img->w = w;
    img->pxs = pxs;

    return img;
}

/*
in: null, img_grey*
out: char*
*/
char* img_gray_to_txt(img_gray* img, char* ascii_ch) {

    // repr for the txt of the string
    char* _repr;
    _repr = (char*)malloc(sizeof(char));
    _repr[0] = '\0';

    // check if img is null
    if (!img) {
        fprintf(stderr, "FATAL ERROR: img is null");
        exit(1);
    }

    // check if img->px is null
    if (!img->pxs) {
        fprintf(stderr, "ERROR: undefined address to px %p", img->pxs);
        exit(1);
    }

    // read img px values into _repr
    for(int row=0; row < img->h; row++) {
        for(int col=0; col < img->w; col++) {

            // find ascii ch for px 
            char ch = px_to_txt(img->pxs[row][col], ascii_ch);
            int old_len = strlen(_repr);
            // allocate memeory and append ch to _repr
            _repr = (char*)realloc(_repr, old_len+2);
            _repr[old_len] = ch;
            _repr[old_len+1] = '\0';

        }
        // append \n to _repr
        char ch  = '\n';
        int old_len = strlen(_repr);
        // allocate memeory and append ch to _repr
        _repr = (char*)realloc(_repr, old_len+2);
        _repr[old_len] = ch;
        _repr[old_len+1] = '\0';
    }

    return _repr;
}


/*
in: 
    px: double in [0...1]
    ascii_ch?: string of ascii characters in ascending brightness 0-1
out: 
    char 

returns the ascii representation of px based on its brightness 0-1
*/
char px_to_txt(double px, char* ascii_ch) {

    // if null use global ascii_ch set by default
    if (!ascii_ch) { ascii_ch = ASCII_CH; }

    // px in 0...bin_size are assigned ascii_ch[0]
    // ...px in (n-1)*bin_size...n*bin_size are assigned ascii_ch[n-1]
    double bin_size = 1.0 / strlen(ascii_ch);
    
    // find correct ch based on bin_size
    // small note if px == 1 its the last bin it bugs otherwise
    char ch = px != 1 ? ascii_ch[(int)floor(px/bin_size)] : ascii_ch[strlen(ascii_ch)-1];

    return ch;
}

// img_gray deconstructor
void free_img_gray(img_gray* img) {
    if (!img) {
        fprintf(stderr, "ERROR: attmpeing to free null img address %p", img);
        exit(1);
    }

    for(int row=0; row < img->h; row++) {
        free(img->pxs[row]);
    }

    free(img->pxs);
    free(img);
}

// int main(int argc, char** argv) {
//     // double px = 0.371;
//     // char ch = px_to_txt(px, " .:10$%");
//     // printf("%f : %c\n", px, ch);

    
//     img_gray* img = create_img_gray(100, 10, 1.0);
//     char* _repr = img_gray_to_txt(img);

//     // for(int i=0; i < img->h; i++) {
//     //     for(int j=0; j < img->w; j++) {
//     //         printf("%f ",img->pxs[i][j]);
//     //     }
//     //     printf("\n");
//     // }
//     printf("%s", _repr);
//     free_img_gray(img);

// }
