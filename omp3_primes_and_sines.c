#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>

int primes[1000];
double sines[1000];
void primesTab(int n){
    int p=0, i=2;
    while (p<n){
        int flag = 1;
        for (int j=2; j<i; j++){
            if (i%j==0){
                flag=0;
                break;
            }
        }
        if (flag)
            primes[p++]=i;
        i++;
    }
}

void sineTab(int n){
    for (int i=0; i<n; i++)
        sines[i] = sin(i*M_PI/180);
}

void main(){
    int n = 10;
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            primesTab(n);
            for (int i=0; i<n; i++)
                printf("Primes %d: %d\n", i, primes[i]);

        }
        #pragma omp section
        {
            sineTab(n);
            for (int i=0; i<n; i++)
                printf("Sin Val %d: %lf\n", i, sines[i]);
        }
    }
}