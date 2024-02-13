#include <stdio.h>
/*
void binaryToHex(int n)
{
    int fourDigits, fourDigitsSum = 0, pow = 1;
    fourDigits = n % 10000;
    n /= 1000;

    if(n != 0) binaryToHex(n);

    while (fourDigits != 0)
    {
        fourDigitsSum += fourDigits%10 * pow;
        pow = pow *2;
        fourDigits /= 10;
    }

    if(fourDigitsSum < 10) printf("%d", fourDigitsSum);
    else
        switch(fourDigitsSum)
        {
            case 10:
                puts("a");
                break;
            case 11:
                puts("b");
                break;
            case 12:
                puts("c");
                break;
            case 13:
                puts("d");
                break;
            case 14:
                puts("e");
                break;
            case 15:
                puts("f");
                break;   
        }
}
*/


int main()
{
    int nBase2, nBase16;

    // scanf("%d", &nBase2);
    // binaryToHex(nBase2);
    scanf("%x", nBase16);
}