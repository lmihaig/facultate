#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <mpi.h>

// functia de integrat f(x)
double f(double x)
{
    return 4. * sqrt(1. - x * x);
}

// functia care calculeaza integrala
double calculeaza_integrala(double a, double b, double c, long n)
{
    long i;
    const gsl_rng_type *T;
    gsl_rng *r;
    double u;
    double x, y;
    long N1 = 0, N2 = 0;
    double I;

    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    for (i = 0; i < n; i++)
    {
        // alege x
        u = gsl_rng_uniform(r);
        //       u = (double) rand()/RAND_MAX;
        x = a + (b - a) * u;
        // alege y
        u = gsl_rng_uniform(r);
        //        u = (double) rand()/RAND_MAX;
        y = c * u;

        //        printf("\n %li %li %f  %f \n",i,n, y, f(x));
        // verifica f(x)<y
        if (y <= f(x))
        {
            N1 = N1 + 1;
        }
        else
        {
            N2 = N2 + 1;
        }
    }
    // valoarea integralei
    I = (double)N1 / (double)n * (b - a) * c;
    return I;
}

int main(int argc, char **argv)
{
    int Np, rank;
    long i;
    // limitele de integrat
    double a, b, c;
    double N;
    double c1, c2;
    long Ni;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &Np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("\n");

    // MASTER -- rang 0
    if (rank == 0)
    {
        double s, I;
        a = 0.;
        b = 1.;
        c = 4.;
        N = 1000000000;

        // trimite a, b, c catre procesele de tip worker
        for (i = 1; i < Np; i++)
        {
            // trimite intervalul de integrare [a, b]
            MPI_Send(&a, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(&b, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);

            // trimite valoarea maxima c
            MPI_Send(&c, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            // trimite numarul de puncte
            Ni = (long)((double)N / (double)Np - 1);
            MPI_Send(&Ni, 1, MPI_LONG, i, 0, MPI_COMM_WORLD);
        }
        // primeste rezultatele integralelor si calculeaza
        // rezultatul final
        I = 0.;
        for (i = 1; i < Np; i++)
        {
            MPI_Recv(&s, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            I = I + s;
        }
        I = I / (double)(Np - 1);
        // afiseaza rezultatul integralei
        printf("I = %.10f \n", I);
    }
    // WORKERS -- rangurile 1, 2, ...,
    else
    {
        double s;
        // primeste intervalul de integrare [a, b]
        MPI_Recv(&a, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&b, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // primeste valoarea maxima c
        MPI_Recv(&c, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // primeste numarul de puncte Ni
        MPI_Recv(&Ni, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%i %f  %f  %f  %li  ", rank, a, b, c, Ni);
        // calculeaza integrala
        s = calculeaza_integrala(a, b, c, Ni);
        printf("s=%f \n", s);
        // trimite rezultatul catre MASTER
        MPI_Send(&s, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}