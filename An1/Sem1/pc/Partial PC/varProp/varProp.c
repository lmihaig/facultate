#include <stdio.h>
#include <string.h>

typedef struct{
    char nume[31], prenume[31], username[31];
    unsigned int pass;
    unsigned short int	grupa;
} Student;

void citire(FILE* fin, int nrStudenti, Student s[])
{
    for(int i = 0 ; i <= nrStudenti; i++)
        fscanf(fin, "%s %s %hu %s %u", &s[i].nume, &s[i].prenume, &s[i].grupa, &s[i].username, &s[i].pass);
}

void printare(FILE* fout, int nrStudenti, Student s[])
{
    for(int i = 0 ; i <= nrStudenti; i++)
        fprintf(fout, "%s %s %hu %s %u \n", s[i].nume, s[i].prenume, s[i].grupa, s[i].username, s[i].pass);
}

void calcNrStudentiGrupa(int nrStudenti, Student s[], short int nrStudentiGrupa[])
{
    for(int i = 0; i <= 3; i++)
        nrStudentiGrupa[i] = 0;
    
    for(int i = 0; i < nrStudenti; i++)
        nrStudentiGrupa[s[i].grupa%10 - 1]++;
}

void codificare(int nrStudenti, Student s[], Student s_codif[])
{
    for(int i = 0 ; i <= nrStudenti; i++)
    {
    strcpy(s_codif[i].nume, s[i].nume);
    strcpy(s_codif[i].prenume, s[i].prenume);
    s_codif[i].grupa = s[i].grupa;
    strcpy(s_codif[i].username, "\0");
    int len = strlen(s[i].username);
    for(int j = len - 1; j >= 0; j--)
        {
            s_codif[i].username[len - j - 1] = s[i].username[j];
        }
    s_codif[i].username[len] = '\0';

    for(int j = 0 ; j < len ; j++)
        s_codif[i].username[j] = s_codif[i].username[j] ^ s_codif[i].nume[j % (sizeof(s_codif[i].nume) / sizeof(char))];
    }
    

}

int main()
{
    FILE* fin = fopen("date.in", "r");
    FILE* fout = fopen("date.out", "w");

    short int nrStudentiGrupa[4];
    Student s[100], s_codif[100];
    int nrStudenti = 100;

    citire(fin, nrStudenti, s);
    codificare(nrStudenti, s, s_codif);
    printare(fout, nrStudenti, s_codif);
}