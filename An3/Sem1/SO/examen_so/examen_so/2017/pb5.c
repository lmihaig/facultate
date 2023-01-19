/*
5. Scrieti o functie in limbajul C:
int signfile(char *director);
care, pentru fiecare fisier obisnuit (regular) din directorul 'director', ce are anul ultimei
actualizari egal cu anul curent din sistem, scrie la sfarsitul fisierului numele proprietarului
acestuia. Functia returneaza numarul fisierelor semnate in acest fel, sau -1 in caz de eroare. Se
vor indica fisierele header necesare.
*/

#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
int signfile(char *director)
{
    DIR *dir = opendir(director);
    char *crt_dir = getcwd(NULL, 0);
    chdir(director);
    if(dir == NULL)
    {
        perror(director);
        return -1;
    }
    struct dirent *entry;
    int nr_fis_semnate = 0;
    while((entry = readdir(dir)) != NULL)
    {
        struct stat filestat;
        if(stat(entry->d_name, &filestat) == -1)
        {
            perror(entry->d_name);
            return -1;
        }
        if(S_ISREG(filestat.st_mode))
        {
            time_t current_time = time(NULL);
            time_t file_timestamp = filestat.st_mtime;

            struct tm *crt_time_1 = gmtime(&current_time);
            struct tm *crt_time_2 = gmtime(&file_timestamp);
            if(crt_time_1->tm_year == crt_time_2->tm_year)
            {
                printf("about to ovewrite file %s\n", entry->d_name);
                FILE *fp = fopen(entry->d_name, "a");
                if(fp == NULL)
                {
                    perror(entry->d_name);
                    exit(EXIT_FAILURE);
                }
            
                struct passwd *userinfo = getpwuid(filestat.st_uid);
                if(userinfo == NULL)
                {
                    perror("getpwuid()"); fclose(fp);
                    return -1;
                }
                fprintf(fp, "%s", userinfo->pw_name);
                fclose(fp);
                nr_fis_semnate++;
            }
        }
    }
    chdir(crt_dir);
    free(crt_dir);
    return nr_fis_semnate;
}

int main()
{
    printf("nr fisiere semnate: %d\n", signfile("fisiere"));
    return 0;
}