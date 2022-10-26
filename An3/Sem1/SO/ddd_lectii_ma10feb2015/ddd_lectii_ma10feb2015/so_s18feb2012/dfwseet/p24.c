#include<unistd.h>
int main(){
  char *argumente[]={"/bin/ls", "-l", NULL};
  execv("/bin/ls", argumente);
  /* in caz de succes al lui "exec", aici nu se mai ajunge */
  return 0;
}
/* Utilizare:
   Lansam:
     p24
   Pe ecran apare efectul executiei unei comenzi shell "ls -l"
*/
