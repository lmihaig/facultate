#include <stdio.h>

int main()
{
    int i, j, n, a[10]={0};
    scanf("%d", &n);
    while (n != 0)
    {
        a[n%10]++;
        n=n/10;
    }

    for(i = 9; i >= 0; i--)
    {
        for(j=0 ; j < a[i]; j++)
            printf("%d", i);
    }

    printf("\n");
    
    for(i = 1; i < 10; i++)
        if(a[i] != 0)
            {
                printf("%d", i);
                a[i]--;
                break;
            }
    for(i = 0; i < a[0]; i++)
        printf("%d", 0);

    for(i = 1; i < 10; i++)
        for(j=0 ; j < a[i]; j++)
            printf("%d", i);

    return 0;
}