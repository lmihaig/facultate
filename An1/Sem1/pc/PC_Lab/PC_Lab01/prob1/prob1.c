#include <stdio.h>

int main()
{
    int x;
    scanf("%d", &x);
    printf("%d %d %d \n", x << 3, x >> 2, (x << 3) + (x << 1));
    if(x & 1) printf("Odd");
    else printf("Even");

}