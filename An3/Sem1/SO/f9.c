#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        fprintf(stderr, "%s <file1> <file2>\n", argv[0]);
        return 1;
    }

    FILE *file1 = fopen(argv[1], "r");

    if (file1 == NULL)
    {
        perror(argv[1]);
        return 1;
    }

    FILE *file2 = fopen(argv[2], "a");
    if (file2 == NULL)
    {
        perror(argv[2]);
        fclose(file1);
        return 1;
    }

    char row[255];

    while (fgets(row, sizeof(row), file1) != NULL)
    {
        fprintf(file2, "%s", row);
    }

    fclose(file1);
    fclose(file2);
    return 0;
}