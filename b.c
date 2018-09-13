#include<mpi.h>
#include<stdio.h>

int main(int argc, char** argv) {
	int rank,size,inp1,inp2;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if (rank==0) {
		scanf("%d", &inp1);
		printf("Master sends %d to slave\n",inp1);
		MPI_Send(&inp1,1,MPI_INT,1,1,MPI_COMM_WORLD);
	}
	if (rank==1) {
		MPI_Recv(&inp2,1,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("%d received by slave \n",inp2);
	}

	MPI_Finalize();

    return 0;
}
