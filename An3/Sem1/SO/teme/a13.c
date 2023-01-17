/*A13. (4 puncte) Scriet un program care verifica daca un numar apare sau nu
 intr-un vector (numarul se vectorul sunt dati ca argumente in linia de
 comanda) printr-o strategie de tip divide et impera: se imparte vectorul in
 doua, apoi se initiaza cate un proces fiu care cauta numarul in fiecare
 jumatate, in aceeasi maniera; cele doua procese se desfasoara in paralel.
 Fiecare subproces returneaza 0 = negasit, 1 = gasit. Fiecare proces nu se
 termina pana nu i se termina toti fii si in final returneaza suma valorilor
 returnate de ei. Procesul initial trebuie in plus sa afiseze un mesaj de tip
 "gasit"/"negasit".*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int divide_and_conquer(long *arr, long left, long right, long num)
{
    if (left < right)
    {
        pid_t left_pid, right_pid;
        int left_status, right_status;
        long middle = left + ((right - left) / 2);

        left_pid = fork();

        if (left_pid < 0)
        {
            fprintf(stderr, "Fork a esuat\n");
            return EXIT_FAILURE;
        }
        else if (left_pid == 0)
        {
            exit(divide_and_conquer(arr, left, middle, num));
        }
        else
        {
            right_pid = fork();
            if (right_pid < 0)
            {
                fprintf(stderr, "Fork a esuat\n");
                return EXIT_FAILURE;
            }
            else if (right_pid == 0)
            {
                exit(divide_and_conquer(arr, middle + 1, right, num));
            }
            else
            {
                left_pid = waitpid(left_pid, &left_status, 0);
                right_pid = waitpid(right_pid, &right_status, 0);
                if (left_pid > 0 && right_pid > 0)
                    if (WIFEXITED(left_status) && WIFEXITED(right_status))
                    {
                        long found = WEXITSTATUS(left_status) + WEXITSTATUS(right_status);
                        return found;
                    }
            }
        }
    }
    else
        return (arr[left] == num) ? 1 : 0;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Utilizare: %s <NUMAR> <VECTOR>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long target = strtol(argv[1], &endptr, 10);

    if (errno != 0)
    {
        fprintf(stderr, "Eroare la conversia numarului \n");
        return 1;
    }

    if (endptr == argv[1] || *endptr != '\0')
    {
        fprintf(stderr, "Argumentul %s invalid\n", argv[1]);
        return 1;
    }

    long size = argc - 2;
    long *arr;
    if ((arr = malloc(sizeof(long) * size)) == NULL)
    {
        fprintf(stderr, "Eroare alocarea memoriei pentru vector\n");
        return 1;
    }

    for (long i = 0; i < size; i++)
    {
        long num = strtol(argv[i + 2], &endptr, 10);

        if (errno != 0)
        {
            fprintf(stderr, "Eroare la conversia numarului \n");
            free(arr);
            return 1;
        }

        if (endptr == argv[i] || *endptr != '\0')
        {
            fprintf(stderr, "Numarul %s invalid\n", argv[i + 2]);
            free(arr);
            return 1;
        }
        else
        {
            arr[i] = num;
        }
    }

    long result = divide_and_conquer(arr, 0, size - 1, target);
    if (result == 0)
    {
        printf("negasit\n");
    }
    else
    {
        printf("gasit\n");
        printf("de %ld ori\n", result);
    }

    return 0;
}