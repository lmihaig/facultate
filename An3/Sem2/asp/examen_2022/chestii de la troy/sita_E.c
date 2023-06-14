/* sita_E.c : Programul implementeaza algoritmul numit "sita lui Eratosthene"
 * pentru gasirea numerelor prime < n, cu o implementare paralela/MPI: 
 * Algoritmul, in pseudocod:
 * 1. Creeaza lista numerelor naturale 2, 3, ..., n
 * 2. k <- 2
 * 3. Repeta
 *   (a) Marcheaza toti multiplii lui k cuprinsi intre k^2 si n
 *   (b) k <- cel mai mic numar nemarcat > k
 *   pana cand k^2 > n
 * 4. Numerele ramase nemarcate sunt prime
 * 
 * Utilizare: mpirun -np N ./sita_E <n>
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/* primul index controlat de procesul id,
 * la rularea cu p procese si n elemente
 */
#define BLOCK_LOW(id,p,n) ((id)*(n)/(p))
/* ultimul index controlat de procesul id,
 * la rularea cu p procese si n elemente
 */
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
/* numarul de elemente controlate de procesul id,
 * la rularea cu p procese si n elemente
 */
#define BLOCK_SIZE(id,p,n) (BLOCK_LOW((id)+1,p,n)-BLOCK_LOW(id,p,n))
/* rangul procesului care controleaza elementul
 * sirului la rularea cu p procese si n elemente
 */
#define BLOCK_OWNER(index,p,n) \
	(((p)*((index)+1)-1)/(n))
/* intoarce cea mai mica dintre valorile transmise ca argumente */
#define MIN(a,b) ((a)<(b)?(a):(b))


int main (int argc, char ** argv)
{
   // durata de executie
   double delta;
   int i;
   int count;		// contorul local pentru numere prime
   int first;		// indexul primului multiplu
   int global_count;	// contorul global pentru numere prime
   int high_val;	// cea mai mare valoare controlata de acest proces
   int low_val;		// cea mai mica valoare controlata de acest proces
   int index;		// indicele in sir al numarului prim curent
   int n;		// limita superioara a sitei (2, ... ,n)
   int prime;		// numarul prim curent
   char * marked;	// portiunea marcata din 2, ... ,n 
   int size;		// elemente in marked
   int proc0_size;	// dimensiunea subsirului procesului 0

   int my_rank, nproc;
   FILE * fp;

   MPI_Init (&argc, &argv);
   
   // cronometrare executie: start
   MPI_Barrier(MPI_COMM_WORLD);
   delta = -MPI_Wtime();

   MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
   MPI_Comm_size (MPI_COMM_WORLD, &nproc);

   // am fost lansati corect in executie?
   if (argc != 2) 
   {
      if (!my_rank) 
      {
         fp = fopen("error.log","a");
         fprintf (fp,"Programul nu a fost lansat corect in executie. \nUtilizare: %s <limita_superiorar>\n", argv[0]);
         fclose(fp); fp = NULL;
      }
      MPI_Finalize(); exit(1);
   }

   // valoarea numerica a argumentului din linia de comanda
   n = atoi(argv[1]);

   /* partea din sirul 2,...,n controlata de procesul curent */
   low_val = 2 + BLOCK_LOW(my_rank,nproc,n-1);
   high_val = 2 + BLOCK_HIGH(my_rank,nproc,n-1);
   size = BLOCK_SIZE(my_rank,nproc,n-1);

   /* iesim daca procesul 0 nu controleaza toate numerele prime din sita */
   proc0_size = (n-1)/nproc;
   if ((2 + proc0_size) < (int) sqrt((double) n)) 
   {
      if (!my_rank) 
      {
         fp = fopen("error.log","a");
         fprintf (fp,"Prea multe procese lansate in executie pentru valoarea %d!\n",n);
         fclose(fp); fp = NULL;
      }
      MPI_Finalize();
      exit(1);
   }

   // alocam partea din sir controlata de acest proces
   marked = (char *) malloc (size);
   if (marked == NULL) 
   {
      fp = fopen("error.log","a");
      fprintf (fp,"Procesul %d: nu pot aloca suficienta memorie!\n",my_rank);
      fclose(fp); fp = NULL;
      MPI_Finalize();
      exit (1);
   }

   // initializare de control
   for (i = 0; i < size; i++) marked[i] = 0;
   if (!my_rank) index = 0;
   
   // cel mai mic numar prim din sir
   prime = 2;

   do {
       if (prime * prime > low_val)
           first = prime * prime - low_val;
       else 
       {
           if (!(low_val % prime)) first = 0;
           else first = prime - (low_val % prime);
       }

       for (i = first; i < size; i += prime) marked[i] = 1;
       
       if (!my_rank) 
       {
           while (marked[++index]);
           prime = index + 2;
       }
       if (nproc > 1) MPI_Bcast (&prime, 1, MPI_INT, 0, MPI_COMM_WORLD);
   } while (prime * prime <= n);

   count = 0;
   for (i = 0; i < size; i++)
       if (!marked[i]) count++;

   if (nproc > 1) MPI_Reduce (&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
   else global_count = count;

   delta += MPI_Wtime();

   if (!my_rank) 
   {
      fp = fopen("output.dat","w");
      fprintf (fp,"%d numere prime sunt cel mult egale cu %d\n", global_count, n);
      fprintf (fp, "Timpul total de executie: %10.6f sec.\n", delta);
      fclose(fp); fp = NULL;
   }

   MPI_Finalize ();
   free(marked);
   return MPI_SUCCESS;
} // end_of_main()


