#include <stdio.h>

int main()
{
     int number, rest = 0, suma = 0, lastNumber = 0, aux = 0;

    FILE *pfile;
    pfile = fopen("prob5.txt", "r");

    fscanf(pfile, "%d", &number);

    while(number)
    {
        if(number == rest) 
            printf("%d %d  ", lastNumber, number);
        suma = 0;
        aux = number;
        while(aux)
            {
                suma += aux%10;
                aux /= 10;
            }
        rest = number%suma;
        lastNumber = number;
        fscanf(pfile, "%d", &number);
    }
   
}