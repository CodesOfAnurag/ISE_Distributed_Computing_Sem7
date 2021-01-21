#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>

#define buffer 32

void main(int argc, char *argv[]){
    int rank, nums, tag=0, temp=1, root=3;
    
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nums);

    char msg[buffer];

    if (rank==3){
        strcpy(msg, "HelloWorld");
        for(temp=0; temp<nums; temp++)
        if (temp!=3)
            MPI_Send(msg, buffer, MPI_CHAR, temp, tag, MPI_COMM_WORLD);
    }
    else{
        MPI_Recv(msg, buffer, MPI_CHAR, root, tag, MPI_COMM_WORLD, &status);
        printf("#%d process receives from #%d process : %s\n", rank, root, msg);
    }
    MPI_Finalize();
}