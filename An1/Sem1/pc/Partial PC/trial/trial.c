#include <stdio.h>
#include <string.h>
int main()
{
    char a = 'a';
    char b[4] = "abc";

    while(a > 0)
        {printf("%d", a%2);
        a = a/2;}
}