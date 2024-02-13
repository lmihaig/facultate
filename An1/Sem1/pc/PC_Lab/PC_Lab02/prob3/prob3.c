#include <stdio.h>

int main()
{
    int n, x, k;
    scanf("%d %d", &n, &x);

    k = (x >> n-1) & 1;
        printf("Al %d-lea bit al lui %d este: %d \n", n, x, k);

    k = x | (1 << n-1);
        printf("Set bit %d: %d \n", n, k);

    k = x & ~(1 << n-1);
        printf("Clear bit %d: %d \n", n, k);
    
    k = x ^ (1 << n-1);
        printf("Toggle bit %d: %d \n", n, k);

}