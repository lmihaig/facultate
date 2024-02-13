#include <stdio.h>
#include <ctype.h>
#include <locale.h>

void afis_clasificare(void)
{
    for (int ndx=0; ndx<=255; ndx++)
    {
        printf("%c %d (0x%02x):\t", ndx, ndx, ndx);
        if(isalnum(ndx)) printf("alnum\t");
        if(isalpha(ndx)) printf("alpha\t");
        if(islower(ndx)) printf("lower\t");
        if(isupper(ndx)) printf("upper\t");
        if(isdigit(ndx)) printf("digit\t");
        if(isxdigit(ndx)) printf("xdigit\t");
        if(iscntrl(ndx)) printf("cntrl\t");
        if(isgraph(ndx)) printf("graph\t");
        if(isspace(ndx)) printf("space\t");
        if(isblank(ndx)) printf("blank\t");
        if(isprint(ndx)) printf("print\t");
        if(ispunct(ndx)) printf("punct");
        printf("\n");
    }
}

int main(void)
{
    afis_clasificare();
    puts(setlocale(LC_ALL, "romanian_Romania.1250"));
    afis_clasificare();
    return 0;
}