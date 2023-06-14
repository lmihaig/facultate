/* Programul evalueaza functia Beta(x,y) a lui Euler, cu o abordare paralela, cu comunicare unilaterala (RMA)
 * Algoritmul: metoda dreptunghiurilor
 *          /1
 * B(x,y) = | t^(x-1) * (1-t)^(y-1) dt 
 *          /0
 * Intervalul (0,1) este divizat in n+1 subintervale; n - definit de procesul MASTER
 */

#include <stdio.h>
#include <math.h>
#include <mpi.h>

// MASTER este procesul pivot pentru RMA
#define MASTER 0

double f(double x, double y, double t)
{
    return pow(t, x-1) * pow(1-t, y-1);
}

int main(int argc, char ** argv)
{
    // Ferestrele pentru RMA
    MPI_Win n_win, val_win;
    
    // pentru algoritm
    double val, xi, dx, sum;
    int i, nproc, my_rank, n;
    
    MPI_Comm wcomm = MPI_COMM_WORLD;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(wcomm, &my_rank);
    MPI_Comm_size(wcomm, &nproc);
    
    //Ferestrele pentru RMA
    if( my_rank == MASTER )
    {
        n = 2000;
        MPI_Win_create(&n, sizeof(int), 1, MPI_INFO_NULL, wcomm, &n_win);
        MPI_Win_create(&val, sizeof(double), 1, MPI_INFO_NULL, wcomm, &val_win);
    }
    else
    {
        /* celelalte procese trebuie sa apeleze in_create, dar nu expun nimic; MPI_BOTTOM desemneaza baza memoriei RAM a proceselor MPI */
        MPI_Win_create(MPI_BOTTOM, 0, 1, MPI_INFO_NULL, wcomm, &n_win);
        MPI_Win_create(MPI_BOTTOM, 0, 1, MPI_INFO_NULL, wcomm, &val_win);
    }
    
    //Procesele de rang non-zero citesc n cu acces unidirectional
    // Deschiderea EE se face cu sincronizare globala
    MPI_Win_fence(0, n_win);
    if(my_rank != MASTER)
        MPI_Get(&n, 1, MPI_INT, MASTER, 0, 1, MPI_INT, n_win);
    // Inchiderea EE se face cu sincronizare globala
    MPI_Win_fence(0, n_win);
    
    val = 0.0; dx = 1.0/(double) n; sum = 0.0;
    
    // fiecare proces poate calcula partea lui din suma totala
    for (i=my_rank + 1; i<=n; i += nproc)
    {
        xi = dx * ((double)i - 0.5);
        sum += f(2,3,xi);
    }
    val = dx * sum;
    
    // Deschidem EE pentru MPI_Accumulate()
    MPI_Win_fence(0, val_win);
    MPI_Accumulate(&val, 1, MPI_DOUBLE, MASTER, 0, 1, MPI_DOUBLE, MPI_SUM, val_win);
    MPI_Win_fence(0, val_win);
    
    if( my_rank == MASTER)
        fprintf(stdout, "B(2,3) = %.8lf\n\n", val);
    
    MPI_Finalize();
    return MPI_SUCCESS;
}//end-of-main()

