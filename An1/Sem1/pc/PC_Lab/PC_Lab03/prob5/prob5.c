#include <stdio.h>

void spiralPrint(int bottom, int right, int a[100][100])
{
    int top=0, left=0, i;

    while((top < bottom) && (left < right))
    {
            for(i = left; i < right; i++)
                printf("%d ", a[top][i]);
            top++;
            for(i = top; i < bottom; i++)
                printf("%d ", a[i][right-1]);
            right--;

            for(i = right-1; i >= left; i--)
                printf("%d ", a[bottom-1][i]);
            bottom--;
           

            for(i = bottom-1; i >= top; i--)
                printf("%d ", a[i][left]);
            left++;
    }
}

int main()
{
    FILE* inputFile;
    inputFile = fopen("prob5.txt", "r");

    int nrLinii, nrColoane, i, j;
    int matrice[100][100];

    fscanf(inputFile, "%d %d", &nrLinii, &nrColoane);

    for(i = 0; i < nrLinii; i++)
        for ( j = 0; j < nrColoane ; j++)
            fscanf(inputFile, "%d", &matrice[i][j]);
    
     spiralPrint(nrLinii, nrColoane, matrice);
    return 0;
}