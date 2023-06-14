/**
 * problema send_recv 
 * (topologie inelara - 
 * de trimis send_data catre rank+1, 
 * de primit in recv_data de la rank-1)
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/**
 * un program MPI cu 4 procese
 * master - rank 0
 * slave - rank 1
 * slave - rank 2
 * slave - rank 3
*/

int main(int argc, char** argv) {
    /**
     * variabile obligatorii
     * nproc - numarul de procese
     * rank - rankul procesului actual
     * root = 0 - rankul procesului master
    */
    int nproc, rank, root = 0;

    // functie obligatorie pentru MPI
    MPI_Init(&argc, &argv);

    // se salveaza in nproc numarul de procese pe comunicatorul world
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    // se salveaza rankul procesului actual pe comunicatorul world
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int send_data[10], recv_data[10];

    /**
     * exemplu proces rank 2
     * send_data[0] = 2
     * 
     * send_data[1] = send_data[0] + 1 = 2 + 1 = 3
     * send_data[2] = send_data[1] + 1 = 3 + 1 = 4
     * ...
     * send_data[9] = send_data[8] + 1 = 10 + 1 = 11
    */
    send_data[0] = rank;
    recv_data[0] = 0;
    for(int i = 1 ; i < 10 ; i++) {
        send_data[i] = send_data[i-1] + 1;
        recv_data[i] = 0;
    }

    /** alta varianta cu acelasi rezultat
     * 
     * for(int i = 0 ; i < 10 ; i++) {
     *   send_data[i] = rank + i;
     *   recv_data[i] = 0;
     * }
    */

    if(rank == root) {
        MPI_Sendrecv(send_data, 10, MPI_INT, rank + 1,
        0,
        recv_data, 10, MPI_INT, nproc - 1,
        0,
        MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else if (rank == nproc - 1) {
        MPI_Sendrecv(send_data, 10, MPI_INT, root,
        0,
        recv_data, 10, MPI_INT, rank - 1,
        0,
        MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        /** MPI_Sendrecv(variabila care se trimite, count, tip_de_date, procesul destinatar,
         *  tag - care poate fi 0,
         * variabila in care se stocheaza bufferul, count, tip_de_date, procesul expeditor,
         * tag - acelasi ca ala de mai sus,
         * MPI_COMM_WORLD - sau alt comunicator, MPI_STATUS_IGNORE - sau ce vreti voi idk)
        */
        MPI_Sendrecv(send_data, 10, MPI_INT, rank + 1,
        0,
        recv_data, 10, MPI_INT, rank - 1,
        0,
        MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    if(rank == root) {
        printf("\n> SEND DATA <\n");
        for(int i = 0 ; i < 10 ; i++) {
            printf("%d ", send_data[i]);
        }
        printf("\n> RECV DATA <\n");
        for(int i = 0 ; i < 10 ; i++) {
            printf("%d ", recv_data[i]);
        }
    }

    MPI_Finalize();
}