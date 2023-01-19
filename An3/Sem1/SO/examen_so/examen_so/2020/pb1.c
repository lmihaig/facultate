#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{   
    pid_t parinte = getpid();
    int k = 5;
    if(fork() != fork()) 
        printf("%d: %d\n", getpid()-parinte+1, ++k); 
    else 
        printf("%d: %d\n", getpid()-parinte+1, --k);
}