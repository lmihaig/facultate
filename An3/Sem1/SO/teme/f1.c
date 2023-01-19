/*F1. (0.5 puncte) Scrieti un program care primeste ca argumente in linia de
 comanda doi intregi si afisaza cmmdc al lor.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b)
{
    int temp;
    while (b != 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        fprintf(stderr, "%s <numar> <numar>", argv[0]);
        return 1;
    }
    char *ptr;

    int a = strtol(argv[1], &ptr, 10);
    if ((*ptr != '\0') || (strlen(argv[1]) == 0))
    {
        fprintf(stderr, "%s invalid>", argv[1]);
        return 1;
    }

    int b = strtol(argv[2], &ptr, 10);
    if ((*ptr != '\0') || (strlen(argv[2]) == 0))
    {
        fprintf(stderr, "%s invalid>", argv[2]);
        return 1;
    }
    if (a == 0 && b == 0)
    {
        puts("nu are sens cmmdc(0,0)\n");
        return 0;
    }

    printf("gcd %d %d: %d", a, b, gcd(a, b));
    return 0;
}