#include <stdio.h>
#include <stdlib.h>  // pentru malloc, calloc, realloc, free


int main()
{
    int i, nr;
    int *vec;
    nr = 10;  // sau cu scanf

    vec = malloc(sizeof(*vec) * nr); // (sizeof(int) * m * n) adik ((size_t * int) * int) 
                                     // calloc(nr, sizeof(*vec))
    //for(i = 0; i < nr; ++i)
    //    vec[i] = i+1;
    for(i = 0; i < nr; i++)
        printf("%d ", vec[i]);
    puts("");

    free(vec);

    return 0;
}