/*
6. Scrieti un program care efectueaza urmatoarele:
- primeste ca argument in linia de comanda in intreg n; daca nu nu este in intervalul 1, ..., 10,
programul se termina cu eroare;
- aloca un tub anonim si genereaza n procese copil conectate la tub a.i. parintele sa citeasca din
tub prin standard input iar copiii sa scrie in el prin standard output; procesele isi vor inchide
ceilalti descriptori la tub;
- parinitele trimite fiecarui copil cate un semnal, ales aleator dintre semnalele 2,3, apoi
asteapta terminarea tuturor copiilor.
- la primirea unui semnal, copilul scrie valoarea lui in tub, apoi se termina;
- dupa terminarea tuturor copiilor, parintele citeste cei n intregi din tub si-i afiseaza pe
standard output
*/
#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

int p[2];

void handler(int signum)
{
    printf("procesul %d scrie %d\n", getpid(), signum);
    write(p[1], &signum, sizeof(int));
    close(p[1]);
    exit(EXIT_SUCCESS);
}
int main(int argc, char **argv)
{
    // initializez germenele cu un nr care difera la fiecare pornite a programului, spre ex timpul curent scurs
    // de la 1 ian 1970 in secunde, sau getpid(), sau orice altceva ce se schimba mereu.
    srand(time(NULL));
    if(argc != 2)
    {
        fprintf(stderr, "Utilizare: %s <nr_intreg>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *ptr = NULL;
    int n = strtol(argv[1], &ptr, 10);
    if(argv[1][0] == '\0' || *ptr != '\0')
    {
        fprintf(stderr, "eroare, nu este un numar %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if(n < 1 || n > 10)
    {
        fprintf(stderr, "n trebuie sa fie intre 1 si 10 nu %d\n", n);
        exit(EXIT_FAILURE);
    }

    // aloca un tub anonim
    if(pipe(p) == -1)
    {
        perror("pipe()");
        exit(EXIT_FAILURE);
    }
    pid_t pid_parinte = getpid();
    signal(2, handler);
    signal(3, handler);
    for(int i = 0; i < n; i++)
    {
        if(getpid() == pid_parinte)
        {
            pid_t pid_copil;
            if((pid_copil = fork()) > 0)
            {
                // parinte
                // trimite aleator un semnal dintre 2,3 copiilor
                int signum = rand()%2 + 2;
                kill(pid_copil, signum);
            }
            else if(pid_copil == 0)
            {
                // copil
                // copiii scriu prin stdout deci nu au nevoie de stdin
                close(p[0]);
                // copilul asteapta primirea semnalului care il omoara
                while(1)
                {
                    sleep(1);
                }
            }
            else{
                // eroare
                perror("fork()");
                exit(EXIT_FAILURE);
            }
        }
    }
    // parintele asteapta copiii
    for(int i = 0; i < n; i++)
        wait(NULL);

    // parintele nu scrie nimic - inchide capul de scriere al tubului
    close(p[1]);
    // toti copiii sunt gata - parintele citeste n intregi si ii afiseaza
    for(int i = 0; i < n; i++)
    {
        int signum;
        read(p[0], &signum, sizeof(int));
        printf("signum = %d\n", signum);
    }
    // eliberare memorie
    close(p[0]);
    return 0;
}