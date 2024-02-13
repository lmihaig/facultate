#include <stdio.h>
#include <string.h>
#include <locale.h>

void afis(const char *locale)
{
    const char* s1 = "notă mică👎";
    const char* s2 = "👍notă MARE";

    printf("In the %s locale: ", locale);
    if(strcoll(s1, s2) < 0)
        printf("%s before %s\n", s1, s2);
    else
        printf("%s before %s\n", s2, s1);
 
    printf("In lexicographical comparison: ");
    if(strcmp(s1, s2) < 0)
        printf("%s before %s\n", s1, s2);
    else
        printf("%s before %s\n", s2, s1);
}

int main(void)
{
    afis("default C");
    puts(setlocale(LC_COLLATE, "ro_RO.utf8"));
    afis("RO");
}