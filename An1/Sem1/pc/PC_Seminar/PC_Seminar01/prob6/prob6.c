#include <stdio.h>

int main()
{
    int a, b;
    long long int lastDigit, pow=1;
    scanf("%d %d", &a, &b);
    lastDigit = a%10;
    if(b == 0)
        printf("%d" , 1);
        else if(lastDigit == 0)
            printf("%d", 0);
            else 
            {
                if(lastDigit == 1)
                    printf("%d" , 1);
                 while(b != 0)
                 {
                     pow*=lastDigit;
                     b--;
                 }
            }
        
    printf("%lld", pow);
    return 1;
}