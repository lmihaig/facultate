#include <stdio.h>

int main()
{
    int n, a1=1, a2=1, a3 = 1;

    scanf("%d", &n);

    for(int i = 3; i <= n  ; i++)
    {   
        a3 = a1 + a2;
        a1 = a2;
        a2 = a3;
    }

    printf("%d", a3);
}