#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    // numarul de procese din comunicator
    int numprocs;
    // rangul procesului
    int rank;

    // Initializare MPI

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Program
    // Nodul 0 trimite un numar intreg x catre nodul 1
    if (rank == 0)
    {
        int x = 2;
        MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    // Nodul 1 primeste numarul intreg x de la nodul 0
    if (rank == 1)
    {
        int x;
        MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf(" Nodul %i: x=%i \n", rank, x);
    }
    // Finalizare MPI
    MPI_Finalize();
    return 0;
}