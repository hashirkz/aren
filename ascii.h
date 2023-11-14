#ifndef ASCII_H
#define ASCII_H

/* 
grayscale img struct
assumes px is pointer to 2d double array where values are 0-1 normalized
*/
typedef struct __img_gray {
    int w;
    int h;
    double** pxs;
}img_gray;

img_gray* create_img_gray(int h, int w, double num);

char* img_gray_to_txt(img_gray* img, char* ascii_ch);

char px_to_txt(double px, char* acsii_ch);

void free_img_gray(img_gray* img);

#endif