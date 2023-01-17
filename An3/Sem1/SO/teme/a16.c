/*A16. (1 punct) Scrieti un program care afisaza valoarea variabilei de
 environment TERM, apoi o asigneaza la valoarea "vt52", apoi genereaza un
 proges fiu (cu fork) care afisaza valoarea lui TERM mostenita.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *print_env(char const *env)
{
    const char *envVal = getenv(env);
    if (envVal != NULL)
    {
        pid_t pid = getpid();
        printf("%s: %s pid: %d\n", env, envVal, pid);
    }

    return envVal;
}

int main()
{
    const char *env_var = "TERM";

    fprintf(stdout, "Actual: ");
    if (print_env(env_var) == NULL)
    {
        fprintf(stderr, "%s nu exista\n", env_var);
        return 1;
    }

    if (setenv(env_var, "vt52", 1) == -1)
    {
        fprintf(stderr, "%s nu a fost setat corect\n", env_var);
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        fprintf(stdout, "Forked pid: %d ", pid);
        if (print_env(env_var) == NULL)
        {
            fprintf(stderr, "%s nu exista\n", env_var);
            return 1;
        }
    }
    else if (pid < 0)
    {
        fprintf(stderr, "Fork a esuat\n");
        return 1;
    }

    return 0;
}