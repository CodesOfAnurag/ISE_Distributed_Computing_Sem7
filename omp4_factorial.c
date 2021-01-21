#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void main(){
    int fact1 = 1, fact2 = 1, i, j;
    printf("Enter n: ");
    int n;
    scanf("%d", &n);
    #pragma omp parallel for firstprivate(n)
    for (i = 2; i<=n; i++)
        fact1*=i;
    
    printf("When firstprivate is not used, factorial of %d: %d\n", n, fact1);
    
    #pragma omp parallel for firstprivate(n, fact2)
    for (j = 2; j<=n; j++)
        fact2*=j;
    
    printf("When firstprivate is not used, factorial of %d: %d\n", n, fact2);
    

}