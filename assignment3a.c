#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define b 20

int position(int [], int);
void sort(int [], int);

void sort(int arr[],int  b){
   int i, min;
   int tmp;

   for(i= b; i > 1; i--) 
   {
      min = position(arr, i);
      tmp = arr[min];
      arr[min] = arr[i-1];
      arr[i-1] = tmp;
   }

int position(int array[], int b) {
   int i, min = 0;
   for (i=0; i<b; i++)
      min = array[i] > array[min] ? i: min;
   return min;
}

void main() {
	int a, b, i, j, arr[length], rec;
    	float ans = 0.0;
    	MPI_Init(NULL, NULL);
    	MPI_Status status;
    	MPI_Comm_rank(MPI_COMM_WORLD, &a);
    	MPI_Comm_size(MPI_COMM_WORLD, &b);
	
	if(a == 0){
		for(i=0; i<length; i++) {
			arr[i] = rand() % length;
		}

		int min = arr[0];
	    int max = arr[0];

	       	for(i=0; i < length; i++) {
	            if(arr[i] < min) { min = arr[i]; }
	            if(arr[i] > max) { max = arr[i]; }
	       }

		int element[b];

		for(int d=1; d < b; d++) {
	                element[d] = 0;
	        }
		for(int d=0; d < b; d++) {
	                int inc = max/(b-1);
	                int itr = 1;
	                bool flag2 = false;
	                for(j = inc; j <= max; j = j + inc) {
	                    if(arr[d] <= j) {
	                        element[itr]++;
	                        flag2 = true;
	                        break;
	                    }
	                    itr++;
	                }
	                if (!flag2) {
	                    element[itr-1]++;
	                }
	       }

		for(int i=1; i<b; i++) {
	                MPI_Send(&element[i], 1, MPI_INT, i, 2, MPI_COMM_WORLD);
	            }

		for(int d=0; d < length; d++) {
	                int inc = max/(b-1);
	                int itr = 1;
	                bool flag = false;
	                for ( j = inc; j <= max; j = j + inc) {
	                    if(arr[d] <= j) {
	                        MPI_Send(&arr[d], 1, MPI_INT, itr, 4, MPI_COMM_WORLD);
	                        flag = true;
	                        break;
	                    }
	                    itr++;
	                }
	                if (!flag) {
	                    MPI_Send(&arr[d], 1, MPI_INT, itr-1, 4, MPI_COMM_WORLD);
	                }
	            }
		int lastIndex = 0, ind = 0, last;
	            for(i=1; i < b; i++) {
	                int recvArray[element[i]];
	                MPI_Recv(&recvArray[0], element[i], MPI_INT, i, 5, MPI_COMM_WORLD, &status);
	                if(last == 0) {
	                    last = element[i];
	                }
	                for(int j=0; j<element[i]; j++) {
	                    arr[ind] = recvArray[j];
	                    ind++;
	                }
	            }
			for(int c = 0 ; c < length ; c++)  {
	                	printf("%d ",arr[c]);
	            }
	}
	 else {
	        int newsize; 
            MPI_Recv(&newsize, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
            int localArray[newsize]; 
	 	 for(int li = 0; li < newsize; li++) {
	        MPI_Recv(&rec, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);
	        localArray[li] =  rec;
	            }
		sort(localArray,newsize);

	MPI_Send(localArray, newsize, MPI_INT, 0, 5, MPI_COMM_WORLD);
	 }
		
	MPI_Finalize();
}

}


