#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<gd.h>

void main(){
    FILE *fp;
    if ((fp = fopen("a1.png", "r"))==NULL){
        printf("File Read Error");
        exit(0);
    }
    
    gdImagePtr img = gdImageCreateFromPng(fp);
    int width = gdImageSX(img);
    int height = gdImageSY(img);

    int x, y, r, g, b, combined, color;
    double t1 = omp_get_wtime();

    #pragma omp parallel for private(y, r, g, b,combined, color)
    for(x=0; x<width; x++){
        #pragma omp critical
        {
            for(y=0; y<height; y++){
                color = gdImageGetPixel(img, x, y);
                r = gdImageRed(img, color);
                g = gdImageGreen(img, color);
                b = gdImageBlue(img, color);
                combined = 0.3*r + 0.59*g + 0.11*b;
                color = gdImageColorAllocate(img, combined, combined, combined);
                gdImageSetPixel(img, x, y, color);
            }
        }
    }

    double t2= omp_get_wtime();

    if ((fp=fopen("a3.png", "w"))==NULL){
        printf("File Error\n");
        exit(0);
    }

    gdImagePng(img, fp);
    gdImageDestroy(img);
    fclose(fp);
    printf("Image Size %dpx x %dpx\n", width, height);
    printf("Time Taken %lfs\n", t2-t1);
    
}