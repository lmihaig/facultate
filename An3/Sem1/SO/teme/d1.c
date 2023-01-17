/*D1. (4 puncte) Program care primeste ca argument in linia de comanda un
 director si afisaza arborescenta de directoare si fisiere cu originea
 in el (similar comenzii tree /f din DOS).*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>

void print_file(char const *file_name, int depth)
{

    for (int i = 1; i <= depth; i++)
        printf("  ");
    printf("└──");

    printf("%s\n", file_name);
}

int tree(const char *dir_name, int depth)
{
    chdir(dir_name);
    DIR *current_dir = opendir(".");
    if (current_dir == NULL)
    {
        perror(dir_name);
        return -1;
    }
    else
    {
        print_file(dir_name, depth);
        struct dirent *data_current_dir;
        while ((data_current_dir = readdir(current_dir)) != NULL)
        {

            if ((strcmp(data_current_dir->d_name, ".") == 0) || (strcmp(data_current_dir->d_name, "..") == 0))
                continue;

            if (data_current_dir->d_type == DT_DIR)
                tree(data_current_dir->d_name, depth + 1);
            else
                print_file(data_current_dir->d_name, depth);

            data_current_dir = readdir(current_dir);
        }
    }
    closedir(current_dir);
    chdir("..");
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <dir>\n", argv[0]);
        return 1;
    }
    tree(argv[1], 0);
}
