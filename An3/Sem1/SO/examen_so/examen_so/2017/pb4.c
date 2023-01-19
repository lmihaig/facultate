/*
4. Scrieti o functie in limbajul C:
 int upcase(char *fis);
care inlocuieste in fisierul 'fis' fisecare litera mica cu litera mare corespunzatoare (restul
caracterelor raman nemodificate); functia returneazanumarul inlocuirilor facute sau -1 in caz de
eroare.
Se va opera direct pe fisierul respectiv (in particular, nu se vor folosi vectori sau fisiere
auxiliare). Se vor indica fisierle header necesare.
Indicatie: literele mici au coduri ASCII consecutive, la fel si literele mari, iar diferenta dintre
codul ASCII al unei litere mici si cel al literei mai corespunzatoare este 32 (codul blankului); ex
'a'-'A'==' '.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int upcase(char *fis)
{
    int fd;
    fd = open(fis, O_RDWR);
    if(fd == -1)
    {
        perror(fis);
        return -1;
    }
    int nr_inlocuiri_facute = 0;

    char ch;
    while(read(fd, &ch, sizeof(char)) > 0)
    {
        if(ch < 'a' || ch > 'z')
            continue;
        // caracterul este lower 'a' <= ch <= 'z'
        ch -= ' '; // il facem upper
        lseek(fd, -1, SEEK_CUR); // ne ducem la pozitia anterioara in fisier
        write(fd, &ch, sizeof(char)); // il suprascriem
        nr_inlocuiri_facute++;
    }
    return nr_inlocuiri_facute;
}
int main()
{
    printf("nr_inlocuiri: %d\n", upcase("fisier_existent.txt"));
   
    return 0;
}