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

    FILE *file2 = fopen(argv[2], "r");
    if (file2 == NULL)
    {
        perror(argv[2]);
        fclose(file1);
        return 1;
    }

    char ch1, ch2;
    do
    {
        ch1 = fgetc(file1);
        ch2 = fgetc(file2);

        if (ch1 != ch2)
        {
            fprintf(stdout, "Fisierele nu sunt egale");
            fclose(file1);
            fclose(file2);
            return -1;
        }

    } while (ch1 != EOF && ch2 != EOF);

    fclose(file1);
    fclose(file2);
    fprintf(stdout, "Fisierele sunt egale");
    return 0;
}