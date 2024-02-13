#include <stdio.h>

int main()
{
    FILE* file;
    file = fopen("prob4.txt", "r");

    int nrColoane, nrLinii, i, j;
    fscanf(file, "%d %d", &nrLinii, &nrColoane);
    int matrice[nrLinii][nrColoane];
    int transpusa[nrColoane][nrLinii];

    for(i = 0; i < nrLinii; i++)
        for(j = 0; j < nrColoane; j++)
            {
            fscanf(file, "%d", &matrice[i][j]);
            transpusa[j][i]=matrice[i][j];
            }

    for(j = 0; j < nrColoane; j++)
    {
        for(i = 0; i < nrLinii; i++)
            {
                printf("%d ", transpusa[j][i]);
            }
        printf("\n");
    }       
    return 0;
}