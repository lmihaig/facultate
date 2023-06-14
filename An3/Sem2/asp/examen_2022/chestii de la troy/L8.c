#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main ( int argc, char **argv)
{
    int i;
    int numprocs, rank;
    int *sbuf;
    int *rbuf;
    int Nr = 10;
    int Ns;
    int root = 0;

    // initializare MPI
    MPI_Init ( &argc, &argv);
    MPI_Comm_size ( MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    Ns = Nr * numprocs;

    // alocare memorie
    if ( rank==root) sbuf = malloc (Ns*sizeof(int));
    rbuf = malloc (Nr*sizeof(int));

    if (rank==root){
        for (i=0; i<Ns; i++){
            sbuf[i] = i+1;
        }
    }
    MPI_Scatter ( sbuf, Nr, MPI_INT, rbuf, Nr,MPI_INT, root, MPI_COMM_WORLD);
    for ( i=0; i<Nr; i++){
        printf ( "rank %i, rbuf[%i] = %i \n", rank, i, rbuf[i]);
    }
    MPI_Finalize();

    return 0;
}

