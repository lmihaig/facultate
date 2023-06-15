#include <iostream>
#include <fstream>
#include <cmath>
#include <gsl/gsl_integration.h>
#include <mpi.h>

double f(double x, void *params)
{
    double alpha = *(double *)params;
    double y = std::log(alpha * x) / std::sqrt(x);
    return y;
}

void printResult(double result, double error)
{
    std::cout << "rezultat = " << result << std::endl;
    std::cout << "eroare estimata = " << error << std::endl;
}

void writeResultToFile(double result, double error)
{
    std::ofstream file("data_2.txt");
    if (file.is_open())
    {
        file << "rezultat = " << result << std::endl;
        file << "eroare estimata = " << error << std::endl;
        file.close();
    }
    else
    {
        std::cout << "Nu s-a putut deschide fisierul data_2.txt" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    int rank, size;
    double a = 0.0, b = 1.0;
    size_t nevals;
    double alpha = 1.0;
    double result, error;

    gsl_integration_cquad_workspace *w = gsl_integration_cquad_workspace_alloc(1000);
    gsl_function F;
    F.function = &f;
    F.params = &alpha;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double subinterval = (b - a) / size;
    double local_a = a + rank * subinterval;
    double local_b = local_a + subinterval;

    gsl_integration_cquad(&F, local_a, local_b, 0, 1e-7, w, &result, &error, &nevals);

    double local_result = result;
    double local_error = error;

    MPI_Reduce(&local_result, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_error, &error, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    gsl_integration_cquad_workspace_free(w);

    if (rank == 0)
    {
        printResult(result, error);
        writeResultToFile(result, error);
    }

    MPI_Finalize();
    return 0;
}
