/*****************************************************************************
 * Programul calculeaza intr-o implementare paralela valoarea medie 
 * mean = sum(x_i)/N si varianta sigma=sum(x_i - mean)^2/(N-1)) unui sir de N
 * valori double, disponibil in fisierul text input_vec.dat.
 * Veti crea doi noi comunicatori, comm1 si comm2, pe baza standard 
 * MPI_COMM_WORLD, subgrupurile asociate group1 continand procesele       
 * cu rang par si respectiv group2 continand procesele cu
 * rang impar din grupul initial. Procesele cu rang 0 din noii
 * comunicatori citesc fisierul de date pe care le redistribuie in mod egal in
 * interiorul acestor comunicatori cu MPI_Scatter(). Primul grup calculeaza 
 * sumele partiale sum(x_i), acumulate de procesul cu rangul zero din comm1
 * care calculeaza valoarea medie, pe care o redistribuie cu MPI_Bcast() in
 * comunicatorul global MPI_COMM_WORLD. Apoi al doilea grup calculeaza sumele
 * partiale sum(x_i -mean)^2, acumulate de procesul cu rangul 0 din comm2.
 * Cele doua procese cu rang 0 afiseaza valorile calculate.
 * ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <mpi.h>

#define N 100
/* prototipul unei functii care afiseaza timpul curent in formatul local,
   definita mai jos, dupa functia main() */
void timestamp ( void );


/******************************************************************************/

int main ( int argc, char **argv )
{
  /* comm1 - comunicatorul asociat subgrupului proceselor cu rang par
   * in comunicatorul global MPI_COMM_WORLD
   * comm2 - comunicatorul asociat subgrupului proceselor cu rang impar
   * in comunicatorul global MPI_COMM_WORLD
   */
  MPI_Comm comm1, comm2;
  
  /* world_group - grupul proceselor din comunicatorul global MPI_COMM_WORLD
   * group1 - subgrupul proceselor cu rang par in comunicatorul
   * global MPI_COMM_WORLD
   * group2 - subgrupul proceselor cu rang impar in comunicatorul
   * global MPI_COMM_WORLD
   * */
  MPI_Group world_group, group1, group2;	
  
  /* my_rank - rangul procesului in MPI_COMM_WORLD
   * new_rank - rangul procesului in comunicatorul nou comm1,
   * sau comm2
   * nproc - numarul de procese lansate in executie (numar par aici!)
   */
  int i, my_rank, new_rank, nproc;
  
  /* mean - valoarea medie mean=sum(x_i)/N
   * sigma - varianta, sigma=sum(x_i - mean)^2 / (N-1)
   * local_sum - variabila folosita de toate procesele pentru calculul sumelor
   * partiale sum(x_i), respectiv sum(x_i - mean)^2, sum(x_i - mean)^2
   * data - bloc alocat dinamic de procesele cu new_rank=0 (cel din 
   * comm1 si cel din comm2), pentru a stoca cele N valori double
   * citite din fisierul input_vec.dat
   * local_data - bloc alocat dinamic de toate procesele, pentru a stoca
   * cele N/(nproc/2) valori double distribuite de procesele cu new_rank=0
   * in comm1 si respectiv in comm2
   */
  double mean, sigma, local_sum,*data,*local_data;	
  
  /* ranks1,ranks2 - blocuri alocate dinamic pentru a stoca
   * rangurile proceselor distribuite in cele doua subgrupuri
   * group1 si group 2, cu ajutorul functiei MPI_Group_incl()
   */  
  int *ranks1, *ranks2;
  
  
/*
  Initializare MPI.
*/
  MPI_Init(&argc, &argv);
  
/*
  Cate procese au fost lansate in executie
*/
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  
/*
  Care-i rangul meu in MPI_COMM_WORLD? Se stocheaza in my_rank.
*/
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

/*
  Procesul 0 in MPI_COMM_WORLD e responsabil cu afisarea unor mesaje 
  (este procesul master).
*/
  if ( my_rank == 0 ) 
  {
    printf("\n");
    printf("Data si ora la inceputul executiei programului: ");
    timestamp ( ); 		// sa afisam data si ora la inceput, intr-un format citibil	
    printf ( "\nCreare de comunicatori MPI - procesul master este cel cu rangul %d\n",my_rank );
    printf ( "\nNumarul de procese lansate in executie este %d.\n", nproc );
    printf ( "\n" );
  }
  

/*
 * Obtin identificatorul grupului asociat lui MPI_COMM_WORLD,
 * stocat in world_group, declarat mai sus,
 * pe care il vom folosi mai jos pentru a defini subgrupuri
*/
  MPI_Comm_group(MPI_COMM_WORLD, &world_group);
  
/*
  ranks1 si ranks2 trebuie alocate dinamic pentru a stoca rangurile
  (valori intregi) pare, respectiv impare (nproc considerat par).
  Fiecare bloc va contine nproc/2 valori intregi.
*/
  ranks1 = (int *) malloc (sizeof(int) * (nproc / 2));
  ranks2 = (int *) malloc (sizeof(int) * (nproc / 2));
  
  /* ranks1 se initializeaza cu rangurile proceselor subgrupului group1, 
   * la momentul crearii (ranguri pare)

   0 1 2 3
   ranks1[0] = 0
   ranks1[1] = 2

   ranks2[0] = 1
   ranks2[1] = 3
   * ranks2 se initializeaz cu valorile rangurilor proceselor subgrupului
   * group2, la momentul crearii (ranguri impare)
   */
  int kpar = 0, kimpar = 0;
  for(int i = 0 ; i < nproc ; i ++) {
    if(i % 2 == 0) {
      ranks1[kpar] = i;
      kpar++;
    } else {
      ranks2[kimpar] = i;
      kimpar++;
    }
  }

  /*
   * extrag subgrupul proceselor de rang par din world_group
   * care va fi referentiat de group1, respectiv al proceselor cu
   * rang impar, care va fi referentiat de group2
   * Procesul cu rang i din group1, respectiv group2, va fi procesul 
   * cu rang ranks[i] din world_group. Functia de utilizat: MPI_Group_incl()
   */
  MPI_Group_incl(world_group, nproc / 2, ranks1, &group1);
  MPI_Group_incl(world_group, nproc / 2, ranks2, &group2);
  
  /*
   * si creez comunicatorii comm1 si comm2 asociati acestor subgrupuri
   * cu MPI_Comm_create()
   */
  MPI_Comm_create(MPI_COMM_WORLD, group1, &comm1);
  MPI_Comm_create(MPI_COMM_WORLD, group2, &comm2);
  
  
/*
 * Noul rang al proceselor din comm1 si comm2 este extras si stocat
 * in new_rank. Atentie: sunt 2 comunicatori!!
 */
  if(my_rank % 2 == 0) {
    MPI_Comm_rank(comm1, &new_rank);
  } else {
    MPI_Comm_rank(comm2, &new_rank);
  }


/*
 * Procesele cu noul rang 0 aloca RAM pentru cele N valori double
 * din input_vec.dat, citesc datele si le distribuie in noii
 * comunicatori (proceselor din noii comunicatori)
 * local_data este alocat de toate procesele pentru a stoca
 * N/(nproc/2) valori double
 */
  if(new_rank == 0) {
    data = (double *) malloc (sizeof(double) * N);
  }


  /* local_data este alocat de toate procesele pentru a stoca
   * N/(nproc/2) valori double
   */
  local_data = (double *) malloc (sizeof(double) * (N / (nproc / 2)));

  
  /* cele doua procese cu new_rank=0 citesc in data cele N
   * valori din fisierul input_vec.dat si le distribuie
   */
  if(new_rank == 0) {
    FILE *f = fopen("input_vec.dat", "r");
    for(int i = 0 ; i < N ; i++) {
      fscanf(f, "%lf", &data[i]);
    }
  }



  /* Datele pot fi distribuite proceselor din comm1 si comm2 cu MPI_Scatter()
   * Atentie, sunt 2 comunicatori comm1 si comm2 si toate procesele de acolo
   * trebuie sa apeleze MPI_Scatter()!
   * Procesele din comm1 calculeaza sumele locale local_sum=sum(x_i), pentru
   * valorile din local_data, apoi valorile local_sum sunt acumulate de procesul
   * cu new_rank=0 in comm1 (de exemplu cu MPI_Reduce()), care calculeaza media
   * si o afiseaza.
   * Procesul cu rang my_rank=0 va distribui tuturor proceselor din comunicatorul 
   * initial MPI_COMM_WORLD
   * de exemplu cu MPI_Bcast(), valoarea mean.
   * Procesele din comm2 calculeaza sumele locale local_sum=sum(x_i - mean)^2, apoi
   * valorile din local_sum sunt acumulate de procesul cu new_rank=0 din comm2, care
   * calculeaza varianta si o afiseaza.
   */
  if(my_rank % 2 == 0) {
    MPI_Scatter(data, N/(nproc/2), MPI_DOUBLE, local_data, N/(nproc/2), MPI_DOUBLE, 0, comm1);
    local_sum = 0.0;
    for(int i = 0 ; i < N/(nproc/2) ; i++) {
        local_sum += local_data[i];
    }
    MPI_Reduce(&local_sum, &mean, 1, MPI_DOUBLE, MPI_SUM, 0, comm1);
    if(new_rank == 0) {
      mean = mean / N;
      MPI_Bcast(&mean, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      printf("\nMedia este: %lf", mean);
    }
  } else {
    MPI_Scatter(data, N/(nproc/2), MPI_DOUBLE, local_data, N/(nproc/2), MPI_DOUBLE, 0, comm2);
    MPI_Bcast(&mean, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    local_sum = 0.0;
    for(int i = 0 ; i < N/(nproc/2); i++) {
      local_sum += (local_data[i] - mean) * (local_data[i] - mean);
    }
    MPI_Reduce(&local_sum, &sigma, 1, MPI_DOUBLE, MPI_SUM, 0, comm2);
    if(new_rank == 0) {
      sigma = sigma / (N-1);
      printf("\nVarianta este: %lf\n", sigma);
    }
  }

 /* se elibereaza resursele alocate si se finalizeaza sesiunea MPI*/
  if(new_rank == 0) {
    free(data);
  }
  free(local_data);
  free(ranks1);
  free(ranks2);


/*
 * Termin sesiunea MPI.
*/
MPI_Finalize();

  
/*
 * ...si aplicatia
*/
  if ( my_rank == 0 )
  {
    printf ( "\n" );
    printf ( "****** Programul a iesit in conditii normale ******\n" );
    printf ( "\n" );
    printf("Data si ora la final: ");
    timestamp ( );
    printf ( "\n" );
  }
  return 0;
}



/******************************************************************************/
void timestamp ( void )
/*
  Rol: afisez data sistemului YMDHMS in formatul nostru local

  Exemplu: 25 June 2020 11:49:54 AM
  Intrare : void
  Iesire : void
*/
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];	// variabila statica: isi conserva valoarea intre apeluri succesive
  const struct tm *tm;
  size_t len;
  time_t now;

  /* time COMMAND : ruleaza COMMAND si intoarce un raport asupra resurselor utilizate
   * aici vreau doar initializarea variabilei now cu timpul sistemului de operare
   */
  now = time ( NULL );
  /* si sa o transformam in ceva mai usor de citit si inteles */
  tm = localtime ( &now );
  
/* formatez stringul reprezentand data si ora intr-un mod mai placut vederii noastre
 * vezi man strftime
 * specificatorii de conversie %d %B %Y %I %M %S %p sunt definiti acolo
 */
  len = strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );
/*si acum sa vedem ce-a iesit */
  fprintf ( stdout, "%s\n", time_buffer );

  return;
# undef TIME_SIZE
}
