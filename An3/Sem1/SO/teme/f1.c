#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Scrieti un program care primeste ca argumente in linia de
//  comanda doi intregi si afisaza cmmdc al lor.

int gcd(int a, int b)
{

    int result = ((a < b) ? a : b);
    if (a == 0)
        return b;
    if (b == 0)
        return a;

    while (result > 0)
    {
        if (a % result == 0 && b % result == 0)
        {
            break;
        }
        result--;
    }
    return result;
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