//Programul separa procesele din grupul comunicatorului
// initial in doua subgrupuri distincte, pe baza rangului
// lor, dupa care sunt creati comunicatorii corespunzatori;
// sunt efectuate operatii de comunicare colective in 
// interiorul acestor comunicatori. 

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// fixam numarul de procese, pentru a asigura functionalitatea corecta
// a programului (acest program are exclusiv un scop ilustrativ)

#define NUMPROCS 6

int main (int argc, char **argv)
{
    int myRank, myNewRank, nProc; // rangul procesului curent,
    // in comunicatorul initial si in cel derivat, si numarul de procese active
    int sendBuf, recvBuf; // bufere pentru operatiile de comunicare colective

    int evenRanks[3] = {0, 2 ,4}; // pentru definirea subgrupului proceselor cu
    // rang initial par
    int oddRanks[3] = {1, 3, 5}; // pentru definirea subgrupului proceselor 
    // cu rang initial impar

    MPI_Group initial_group, new_group;// handlere pentru grupul 
    // comunicatorului initial si pentru noul grup
    MPI_Comm initial_comm = MPI_COMM_WORLD, new_comm;// handlere pentru
    //comunicatorul initial si pentru noul comunicator

    MPI_Init (&argc, &argv);// initializarea mediului MPI, numai
    //dupa acest pas pot fi apelate functiile MPI
    MPI_Comm_rank (initial_comm, &myRank);// rangul procesului curent
    //in comunicatorul implicit
    MPI_Comm_size(initial_comm, &nProc);// numarul de procese active

    //Pentru a asigura functionalitatea programului, fortam lansarea
    //in executie a NUMPROCS procese, in caz contrar terminand
    //sesiunea MPI curenta

    if (nProc != NUMPROCS)
    {
        if (myRank == 0)
        printf("Programul functioneaza corect numai daca sunt lansate in executie %d procese. Ies... \n", NUMPROCS);
        MPI_Finalize(); // terminam sesiunea MPI curenta inainte de iesire
        exit(1); // si iesim cu cod 1

    }
    //stocam rangul initial in sendBuf
    sendBuf = myRank;
    //apelam MPI_Comm_group(), pentru a obtine un handle pentru
    //grupul initial
    MPI_Comm_group (initial_comm, &initial_group);
    //cream cele doua grupuri de procese distincte, pe baza
    //valorii rangului initial (par sau impar)
    if (myRank % 2)
    MPI_Group_incl(initial_group, 3, oddRanks, &new_group);
    //subgrupul proceselor cu rang impar
    else
    MPI_Group_incl (initial_group, 3, evenRanks, &new_group);
    //subgrupul proceselor cu rang par
    //cream noul comunicator, caruia ii este asociat new_group
    MPI_Comm_create (initial_comm, new_group, &new_comm);
    //new_comm contine grupuri distincte pe procesele cu rang par/impar
    
    //rangul procesului curent in noul grup
    MPI_Group_rank(new_group, &myNewRank);

    // operatie colectiva:se aduna valorile sendBuf din toate procesele dintr-un
    //grup si se intoarce rezultatul recvBuf de pe procesele cu rangul nou 0

    MPI_Reduce(&sendBuf, &recvBuf, 1, MPI_INT, MPI_SUM, 0, new_comm);
    //afisam cateva informatii cu rol demonstrativ (se sumeaza valorile sendBuf
    //din toate procesele dintr-un grup si se intoarce rezultatul in recvBuf
    //de pe procesele cu rangul nou 0 - acum doua asemenea procese)

    if (myNewRank == 0)
    printf ("Procesul cu rangul initial = %d, noul rang=%d, are recvBuf=%d\n",myRank,
    myNewRank, recvBuf);

    //terminam sesiunea MPI
    MPI_Finalize();
    // si iesim
    return 0;



}