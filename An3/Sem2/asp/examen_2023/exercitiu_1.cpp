#include <iostream>
#include <fstream>
#include <mpi.h>
#include <gsl/gsl_rng.h>

#define ARRAY_SIZE 10

int main(int argc, char **argv)
{
    int my_rank, size;
    double data[ARRAY_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    gsl_rng *rng = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set(rng, my_rank);

    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        data[i] = gsl_rng_uniform(rng);
    }

    if (my_rank == 0)
    {
        std::ofstream file("data_1.txt");
        if (!file)
        {
            std::cerr << "Eroare la deschiderea fisierului!\n";
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        file << "rank: " << my_rank << " ";
        for (int i = 0; i < ARRAY_SIZE; ++i)
        {
            file << data[i] << " ";
        }
        file << "\n";

        for (int i = 1; i < size; ++i)
        {
            MPI_Recv(data, ARRAY_SIZE, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            file << "rank: " << i << " ";
            for (int j = 0; j < ARRAY_SIZE; ++j)
            {
                file << data[j] << " ";
            }
            file << "\n";
        }

        file.close();
    }
    else
    {
        MPI_Send(data, ARRAY_SIZE, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    gsl_rng_free(rng);

    MPI_Finalize();

    return 0;
}
