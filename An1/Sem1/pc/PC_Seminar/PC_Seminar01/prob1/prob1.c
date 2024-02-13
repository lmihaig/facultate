#include <stdio.h>  
int main()
{
    int max1, max2, n, i, aux, x;

    FILE * pfile;
    pfile = fopen("input.txt", "r");

    scanf("%d", &n);
    fscanf(pfile, "%d %d", &max1, &max2) ;
    
    
    if(max1 > max2)
    {
        aux = max1;
        max1 = max2;
        max2 = max1;
    }

    for( int i = 2; i< n; i++)
        {
            fscanf(pfile, "%d", &x);
            if(x > max2 && x!= max1)
            {
                max1 = max2;
                max2 = x;
            }
            else if(x > max1 && x!=max2)
                {
                    max1 = x;
                }
        }
    if(max1 == max2)
        printf("Imposibil");
    else
        printf("%d %d", max1, max2);
    return 0;
}