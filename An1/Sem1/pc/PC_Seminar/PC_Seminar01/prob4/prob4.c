#include <stdio.h>

int main()
{
    int i, n, nrCif = 0, copie, sum = 0, lastDigit, pow = 1;
    scanf("%d", &n);
   
    copie = n;
    while(copie != 0)
        {
            copie/=10;
            nrCif++;
        }
    while(n != 0)
    {
        lastDigit = n%10;
        for(i=1; i <= nrCif; i++)
            {
                sum+= lastDigit*pow;
                pow*= 10;
            }
        pow = 1;
        n/=10;
    }
    printf("%d", sum);
}