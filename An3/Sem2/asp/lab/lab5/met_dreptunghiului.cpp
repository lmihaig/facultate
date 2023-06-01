// Calculul unei integrale

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
// functia de integrat f(x)
double f(double x)
{
    return 4. * sqrt(1. - x * x);
}
// functia care calculeaza integrala
double calculeaza_integrala(double a, double b, long N)
{
    int i;
    double dx = (b - a) / (double)N;
    double x;
    double s;
    s = 0;
    for (i = 0; i < N; i++)
    {
        x = a + (double)i * dx + dx / 2.;
        s = s + f(x);
    }
    s = s * dx;
    return s;
}
int main(int argc, char **argv)
{
    int Np, rank;
    long i;
    // limitele de integrare
    double a, b;
    double N;
    double c1, c2;
    long Ni;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &Np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // MASTER -- rang 0
    if (rank == 0)
    {
        double s, I;
        // input
        a = 0.;
        b = 1.;
        N = 10000;
        // trimite a , b catre procesele de tip worker
        for (i = 1; i < Np; i++)
        {
            // trimite intervalul de integrare [ c1 , c2 ]
            c1 = a + (b - a) / (double)(Np - 1) * (double)(i - 1);
            c2 = a + (b - a) / (double)(Np - 1) * (double)i;
            Ni = (long)((double)N / (double)(Np - 1));
            MPI_Send(&c1, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(&c2, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(&Ni, 1, MPI_LONG, i, 0, MPI_COMM_WORLD);
        }
        // primeste rezultatele integralelor si calculeaza
        // rezultatul final
        for (i = 1; i < Np; i++)
        {
            MPI_Recv(&s, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0,
                     MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            I = I + s;
        }
        // afiseaza rezultatul integralei
        printf("I = % f \n", I);
    }
    // WORKERS -- rangurile 1, 2, ... ,
    else
    {
        double s;
        // primeste intervalul de integrare
        MPI_Recv(&c1, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        MPI_Recv(&c2, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        MPI_Recv(&Ni, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        // calculeaza integrala pe intervalul [c1 , c2 ]
        s = calculeaza_integrala(c1, c2, Ni);
        // trimite rezultatul catre MASTER
        MPI_Send(&s, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}