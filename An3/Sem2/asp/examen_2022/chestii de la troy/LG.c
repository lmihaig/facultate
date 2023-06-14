#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main ( int argc, char **argv)
{
    int i;
    int numprocs, rank;
    int *sbuf;
    int *rbuf;
    int N = 10; // N elemente in fiecare proces
    int root = 0;

    //initializare MPI

    MPI_Init ( &argc, &argv);
    MPI_Comm_size ( MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank ( MPI_COMM_WORLD, &rank);

    // alocare memorie
    sbuf = malloc (N*sizeof(int));
    if (rank==root) rbuf = malloc ( N*numprocs*sizeof(int));

    for (i=0; i<N; i++){
        sbuf[i] = rank*100 + i;
    }
    MPI_Gather (sbuf, N, MPI_INT, rbuf, N, MPI_INT, root, MPI_COMM_WORLD);

    if (rank==0) {
        for ( i=0; i<N*numprocs; i++){
        
        printf ("rbuf[%i] = %i \n", i, rbuf[i]);
    }
}


    MPI_Finalize();

    return 0;
}