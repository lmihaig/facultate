#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main ( int argc, char **argv)
{
    int i;
    int numprocs, rank;
    int x;
    int root = 1;

    // Initializare MPI
    MPI_Init ( &argc, &argv);
    MPI_Comm_size ( MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank ( MPI_COMM_WORLD, &rank);

    x = rank +1;

    MPI_Bcast ( &x, 1, MPI_INT, root, MPI_COMM_WORLD);
    printf ( " Rank %i, x = %i \n", rank, x);
    MPI_Finalize ();

    return 0;
}