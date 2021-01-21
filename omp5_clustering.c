#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define K 4
int num_points;
long cluster[K][2] = {{75, 75}, {75, 25}, {25, 75}, {25, 25}};
long datapoints[100][2];
int cluster_count[K];

void populate(){
    int i=0;
    #pragma omp parallel
    for(i=0; i<num_points; i++){
        datapoints[i][0] = rand()%100;
        datapoints[i][1] = rand()%100;
    }
}

long distance(int x1, int x2, int y1, int y2){
    return (long) sqrt(pow((x2-x1), 2)+pow((y2-y1), 2));
}

void clustering(){
    int i, j, curr_dist, min_dist, cluster_index;
    #pragma omp parallel for private(i, j, min_dist, curr_dist, cluster_index)
    for(i=0; i<num_points; i++){
        cluster_index=0;
        min_dist=999;
        for (j=0; j<K; j++){
            curr_dist = distance(datapoints[i][0], cluster[j][0], datapoints[i][1], cluster[j][1]);
            if (min_dist>curr_dist){
                min_dist = curr_dist;
                cluster_index = j;
            }
        }
        printf("(%ld, %ld) belongs to cluster#%d (%ld, %ld)\n", datapoints[cluster_index][0], datapoints[cluster_index][1], cluster_index+1, cluster[cluster_index][0], cluster[cluster_index][0]);
        cluster_count[cluster_index]++;
    }
}

void main(){
    printf("Enter number of datapoints: ");
    scanf("%d", &num_points);

    populate();
    
    double t1 = omp_get_wtime();
    clustering();
    double t2 = omp_get_wtime();
    
    printf("Time Taken: %lf\n", t2-t1);

    printf("Cluster Counts\n");
    for (int i = 0; i<K; i++)
        printf("Cluster#%d -> %d points\n", i+1, cluster_count[i]);

}