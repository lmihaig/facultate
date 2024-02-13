#include <stdio.h>
#include <limits.h>

int main()
{   
    printf("Un `int` ocupa %zu bytes (%zu de biti).\n", sizeof(int), CHAR_BIT*sizeof(int));
    printf("Un `double` ocupa %zu bytes (%zu de biti).\n", sizeof(double), CHAR_BIT*sizeof(double));
    printf("Un `long double` ocupa %zu bytes (%zu de biti).\n", sizeof(long double), CHAR_BIT*sizeof(long double));
    printf("Un `float` ocupa %zu bytes (%zu de biti).\n", sizeof(float), CHAR_BIT*sizeof(float));
    return 0;
}