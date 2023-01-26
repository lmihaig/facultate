#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
int main()
{
    int k = 10;
    pid_t pid_parinte = getpid();
    if( fork() && !fork()) --k; else ++k;
    printf("%d: %d\n", getpid()-pid_parinte+1, k);
}