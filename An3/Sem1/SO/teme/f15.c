/* F15. (1.5 puncte) Scrieti un program ce simuleaza comanda "cat", cu tot cu
  cazul cand specificatorul fisierului este dat ca argument in linia de
  comanda. Programul va putea fi lansat astfel astfel:
    cat f   ==>  citeste din f si scrie la stdout
    cat     ===> citeste de la stdin si scrie la stdout*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int write_to_fd(int fd, const void *buf, int len)
{
    while (len)
    {
        int write_size = write(fd, buf, len);

        if (write_size < 0)
            return 0;

        buf = (char *)(buf) + write_size;
        len -= write_size;
    }

    return 1;
}

int read_to_fd(int read_fd, int write_fd)
{
    char buff[1024];
    while (1)
    {

        int len = read(read_fd, buff, sizeof(buff));
        if (len == -1)
        {
            perror("Eroare la citire");
            return 1;
        }
        if (len == 0)
            // eof
            return 0;
        write_to_fd(write_fd, buff, len);
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
        read_to_fd(fileno(stdin), fileno(stdout));
    else if (argc == 2)
    {
        int read_fd = open(argv[1], O_RDONLY);
        if (read_fd == -1)
        {
            perror(argv[1]);
            return 1;
        }
        read_to_fd(read_fd, fileno(stdout));
        close(read_fd);
    }
    return 0;
}