#include <stdio.h>

int main()
{
    FILE *inputFile;
    inputFile = fopen("prob7.txt", "r");

    int n, i, j, matrice[101][101], x;

    fscanf(inputFile, "%d", &n);
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            fscanf(inputFile, "%d", &matrice[i][j]);

    
    for(i = 0; i < n/2; i++)
    {
        x = matrice[i][i];

        for(j = i; j < n-i-1; j++)
            matrice[j][i] = matrice[j+1][i];

        for(j = i; j < n-i-1; j++)
            matrice[n-i-1][j] = matrice[n-i-1][j+1];

        for(j = n-i-2; j >= i; j--)
            matrice[j+1][n-i-1] = matrice[j][n-i-1];

        for(j = n-i-2; j > i; j--)
            matrice[i][j+1] = matrice[i][j];
        matrice[i][i+1] = x;
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            printf("%3d", matrice[i][j]);
        printf("\n");
    }

}