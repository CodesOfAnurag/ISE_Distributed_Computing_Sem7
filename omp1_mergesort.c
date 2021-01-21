#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void merge(int a[], int l, int m1, int m2, int r){
    int i=l, j=m2 , k=0, temp[1000];
    while (i<=m1 && j<=r)
        if (a[i]<a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    while (i<=m1)
        temp[k++] = a[i++];
    while (j<=r)
        temp[k++] = a[j++];
    for (i=l, j=0; i<=r; i++, j++)
        a[i] = temp[j];
}

void mergesort(int a[], int l, int r){
    int mid;
    if (l<r){
        mid = (l+r)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                printf("Left Branch at id : %d\n", omp_get_thread_num());
                mergesort(a, l, mid);
            }
            #pragma omp section
            {
                printf("Right Branch at id : %d\n", omp_get_thread_num());
                mergesort(a, mid+1, r);
            }
        }
        merge(a, l , mid, mid+1, r);
    }
}

void main(){
    int n;
    printf("N(elements): ");
    scanf("%d", &n);
    
    int a[n];
    printf("Unsorted Array: ");
    for (int i = 0; i<n; i++){
        a[i] = rand()%100;
        printf("%d ", a[i]);
    }
    printf("\n");

    mergesort(a, 0, n-1);
    printf("Sorted Array: ");
    for (int i = 0; i<n; i++)
        printf("%d ", a[i]);
    printf("\n");
}