#include <stdio.h>

int main()
{
    int n, i;
    float x1, x2, difmax=0;
    int zi=0;

    FILE *pfile;
    pfile = fopen("input.txt","r");
    
    fscanf(pfile, "%d", &n);

    fscanf(pfile, "%f", &x1);
    for(i = 2; i <= n+1; i++)
    {
        fscanf(pfile, "%f", &x2);
        if( x2 - x1 > difmax)
            {
                difmax = x2 - x1;
                zi=i;
            }
    }

    printf("%.2f %d %d", difmax, zi-1, zi);

}