#include <stdio.h>
#include <stdlib.h>

int prim(int x)
{
    if (x < 2)
        return 0;

    for (int i = 2; i < x; i++)
    {
        if (x % i == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "./f2.exe <numar>");
        return -1;
    }
    char *ptr;

    int a = strtol(argv[1], &ptr, 10);

    if (prim(a))
        printf("%d e prim", a);
    // printf("%d", prim(a));

    else
        printf("%d nu e prim", a);
    // printf("%d", prim(a));

    return 0;
}