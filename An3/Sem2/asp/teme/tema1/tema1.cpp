#include <iostream>
#include <fstream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    int N = 200;
    int my_rank, my_new_rank, nproc;
    int *low_ranks, *high_ranks;
    float *a, *x, *y;
    float *a_loc, *x_loc, *y_loc;
    float mel = 0, mel_loc = 0., ps = 0, ps_loc = 0.;
    MPI_Comm world_comm = MPI_COMM_WORLD, low_comm, high_comm;
    MPI_Group world_group, low_group, high_group;
    MPI_Comm my_comm;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(world_comm, &my_rank);
    MPI_Comm_size(world_comm, &nproc);

    int per_group = nproc / 2;
    low_ranks = new int[per_group];
    high_ranks = new int[per_group];

    for (int i = 0; i < nproc; i++)
    {
        if (i < (per_group))
            low_ranks[i] = i;
        else
            high_ranks[i - (per_group)] = i;
    }

    my_new_rank = my_rank % per_group;

    MPI_Comm_group(world_comm, &world_group);

    MPI_Group_incl(world_group, per_group, low_ranks, &low_group);
    MPI_Group_incl(world_group, per_group, high_ranks, &high_group);

    MPI_Comm_create(world_comm, low_group, &low_comm);
    MPI_Comm_create(world_comm, high_group, &high_comm);

    int is_low_group = my_rank < per_group;

    my_comm = is_low_group ? low_comm : high_comm;

    x_loc = new float[N / per_group];
    y_loc = new float[N / per_group];
    a = new float[N * N];
    y = new float[N];
    if (my_new_rank == 0)
    {
        x = new float[N];

        ifstream ain("mat.dat");
        ifstream xin("x.dat");
        ifstream yin("y.dat");

        for (int i = 0; i < N; i++)
        {
            xin >> x[i];
            yin >> y[i];
        }

        for (int i = 0; i < N * N; i++)
        {
            ain >> a[i];
        }
    }
    MPI_Scatter(x, N / per_group, MPI_FLOAT, x_loc, N / per_group, MPI_FLOAT, 0, my_comm);
    MPI_Scatter(y, N / per_group, MPI_FLOAT, y_loc, N / per_group, MPI_FLOAT, 0, my_comm);
    MPI_Bcast(a, N * N, MPI_FLOAT, 0, my_comm);
    MPI_Bcast(y, N, MPI_FLOAT, 0, my_comm);
    int offset = my_new_rank * (N / per_group);
    if (is_low_group)
    {
        // numarator
        for (int i = 0; i < N / per_group; i++)
        {
            for (int j = 0; j < N; j++)
            {
                mel_loc += x_loc[i] * y[j] * a[(i + offset) * N + j];
            }
        }
        MPI_Reduce(&mel_loc, &mel, 1, MPI_FLOAT, MPI_SUM, 0, my_comm);
    }
    else
    {
        // numitor
        for (int i = 0; i < N / per_group; i++)
        {
            ps_loc += x_loc[i] * y_loc[i];
        }
        MPI_Reduce(&ps_loc, &ps, 1, MPI_FLOAT, MPI_SUM, 0, my_comm);
        if (my_new_rank == 0)
        {
            MPI_Send(&ps, 1, MPI_FLOAT, 0, 0, world_comm);
        }
    }

    if (my_rank == 0)
    {
        MPI_Recv(&ps, 1, MPI_FLOAT, per_group, 0, world_comm, MPI_STATUS_IGNORE);
        ofstream res("res.dat");
        res << "AVG = " << mel / ps;
    }

    delete[] x;
    delete[] y;
    delete[] a;
    delete[] low_ranks;
    delete[] high_ranks;
    MPI_Finalize();
    return 0;
}