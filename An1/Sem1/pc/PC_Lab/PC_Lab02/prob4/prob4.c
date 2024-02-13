#include <stdio.h>

int main()

{
    int i, n, x, y, p, bitY;
    scanf("%d %d %d %d", &x, &p, &n, &y);

    for(i = p; i >= p-n+1 ; i--)
    {
        bitY = (y >> i) & 1;

        if(bitY)
            x = x | (1 << i);
        else
            x = x & ~(1 << i);
    }

    printf("\n %d", x);

    return 0;
}

/*
0001000 = 8
1100101 = 101
   ^  ^
   p p-n+1
1101000 = 104
101 3 4 8 => 104 
*/