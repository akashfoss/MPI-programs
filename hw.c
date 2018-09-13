#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  
MPI_Init(NULL, NULL);

  int size, rank, len;
  char name[MPI_MAX_PROCESSOR_NAME];

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(name, &len);

  printf("Hello world from processor %s, rank %d out of %d processors\n", name, rank, size);

  MPI_Finalize();

  return 0;
}

