#include <mpi.h>
#include <stdio.h>

MPI_Finalize();

void main() {
        int a, b, i, j;
        float clock = 0.0;

        MPI_Init(NULL, NULL);
        MPI_Status status;
        
        MPI_Comm_rank(MPI_COMM_WORLD,&a);
        MPI_Comm_size(MPI_COMM_WORLD,&b);

        int l[b][b],b[b];
        float x[b];

        for(i = 0; i < b; i++){
            for(j = 0; j <= i; j++){
                scanf("%d", &l[i][j]);
            }
                scanf("%d", &b[i]);
        	}

        if(a == 0){
                x[a] = (float)b[a] / l[a][a];
		printf("x[%d] = %f ", a, x[a]);
		MPI_Send(&x[0],1, MPI_FLOAT, 1, 1, MPI_COMM_WORLD);
		
        }

	   else if(a < b-1){
            clock = 0.0;
            for(i = 0; i < a; i++){
			MPI_Recv(&x[i], 1, MPI_FLOAT, a - 1, 1, MPI_COMM_WORLD, &status);
			printf("x[%d] = %f ", i, x[i]);
			MPI_Send(&x[i], 1, MPI_FLOAT, a + 1, 1, MPI_COMM_WORLD);
                }
		
        for(i = 0; i < a; i++){
			clock += l[a][i] * x[i];
		}
                x[a] = (float)(b[a]-clock) / l[a][a];
		printf("x[%d] = %f ", a, x[a]);
		MPI_Send(&x[a], 1, MPI_FLOAT, a + 1, 1, MPI_COMM_WORLD);
        }

        else {
		
        for(i = 0; i < a; i++){
			MPI_Recv(&x[i], 1, MPI_FLOAT, a - 1, 1, MPI_COMM_WORLD,&status);
		}
		
        for(i = 0; i < a; i++){
			clock += l[a][i] * x[i];
		}
                x[a] = (float)(b[a]-clock) / l[a][a];
		printf("x[%d] = %f ", a, x[a]);
	}
}