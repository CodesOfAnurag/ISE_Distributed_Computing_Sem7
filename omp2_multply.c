#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void main(){
    
    int rows, cols, vsize, i, j;
    printf("Enter rows, cols, vsize: ");
    scanf("%d%d%d", &rows, &cols, &vsize);

    if (rows<=0 && cols<=0 && vsize<=0 && cols!=vsize){
        printf("Invalid Sizes\n");
        exit(0);
    }

    int matrix[rows][cols];
    printf("Matrix:\n");
    for (i=0; i<rows; i++){
        for (j=0; j<cols; j++){
            printf("%d\t", i+j);
            matrix[i][j] = i+j;
        }
        printf("\n");
    }

    int vector[vsize];
    printf("Vector: \n");
    for (i=0; i<vsize; i++){
        vector[i] = i;
        printf("%d\t", i);
    }
    printf("\n");

    int result[rows];
    for (i=0; i<rows; i++)
        result[i] = 0;   

    #pragma omp parallel for private(j)
    for(i=0; i<rows; i++)
        for(j=0; j<cols; j++)
            result[i] += matrix[i][j]*vector[j];
    
    printf("Result: \n");
    for(i=0; i<rows; i++)
        printf("%d\t", result[i]);
    printf("\n");
}