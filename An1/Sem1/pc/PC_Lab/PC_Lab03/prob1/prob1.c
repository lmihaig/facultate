#include <stdio.h>

int main()
{
    int i, n, m, comune = 0, numar;
    int frecventa[4000] = {0};

    FILE *pfile;
    pfile = fopen("prob1.txt", "r");

    fscanf(pfile, "%d %d", &n, &m);

    for(i = 0; i < n+m; i++)
    {   
        fscanf(pfile, "%d", &numar);
        if(++frecventa[numar+2000] == 2) 
            comune++;
    }
    printf("%d", comune);

return 0;
}