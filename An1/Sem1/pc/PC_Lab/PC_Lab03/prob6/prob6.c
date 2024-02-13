#include <stdio.h>
#include <math.h>

int primcheck(int n)
{
    int i;
    if(n < 3) return 0;
    if(n%2 == 0) return 2;
    for(i = 3; i <= sqrt(n); i+=2)
        if(n%i == 0) return i;
    return 0;
}

int main()
{
    int n, m, matrice[100][100], i, j = 1, LEFT = 0, TOP = 0, a[200], x;
    
    scanf("%d %d", &n, &m);

// O(n*m)
    for(i = 0; i < n*m; i++)
    {
        x = primcheck(j);
        if(!x) a[i] = j;
        else 
        {
            a[i] = j;
            a[i+1] = x;
            i++;
        }
        j++;
    }

// O(n*m)
    int BOTTOM = n, RIGHT = m;
    j = 0;
    while((TOP < BOTTOM) && (LEFT < RIGHT))
    {   
            for(i = LEFT; i < RIGHT; i++)
                {
                    matrice[TOP][i] = a[j];
                    j++;
                }
            TOP++;

            for(i = TOP; i < BOTTOM; i++)
                {
                    matrice[i][RIGHT-1] = a[j];
                    j++;
                }
            RIGHT--;

            for(i = RIGHT-1; i >= LEFT; i--)
                {
                    matrice[BOTTOM-1][i] = a[j];
                    j++;
                }
            BOTTOM--;
           
            for(i = BOTTOM-1; i >= TOP; i--)
                {
                    matrice[i][LEFT] = a[j];
                    j++;
                }
            LEFT++;
    }
// O(n)
    for(i = 0 ; i < n ; i++)
    {
        for(j = 0; j < m; j++)
            printf("%d \t", matrice[i][j]);
        putchar('\n');
    }
    return 0;
}

/*
 1   2   3   4   2
11  12   2  13   5
 2  16   2  14   6
10   3  15   2   2
 3   9   2   8   7
 */