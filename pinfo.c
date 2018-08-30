#include "headers.h"

void pinfo(char *token)
{
    // struct stat st;
    // token = strtok(NULL, " ");
    // if (token == NULL)
    // {
    //     int pid = getpid();
    //     printf("pid -- %d\n", pid);

    // }
    // return;
    char stat[1000];
    char exec[1000];
    int c = 0;
    char st[100][100];
    while (token != NULL)
    {
        strcpy(st[c++], token);
        token = strtok(NULL, " \n\t\r");
    }
    //printf ("c %d\n", c);
    if (c > 1)
    {
        strcpy(stat, "/proc/");
        strcat(stat, st[1]);
        strcat(stat, "/stat");
        strcpy(exec, "/proc/");
        strcat(exec, st[1]);
        strcat(exec, "/exe");
    }
    else
    {
        char buff[40];
        sprintf(buff, "%d", getpid());
        //printf("buff: %s\n", buff);
        strcpy(stat, "/proc/");
        strcat(stat, buff);
        strcat(stat, "/stat");
        strcpy(exec, "/proc/");
        strcat(exec, buff);
        strcat(exec, "/exe");
    }
    //printf ("%s %s\n", stat, exec);
    FILE *fd;
    if ((fd = fopen(stat, "r")) == NULL)
        printf("Error: Process desn't exist\n");
    else
    {
        int pid;
        char status;
        long unsigned memory;
        fscanf(fd, "%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &pid, &status, &memory);
        fclose(fd);
        printf("pid -- %d\n", pid);
        printf("Process Status -- %c\n", status);
        printf("Memory -- %lu\n", memory);
    }
}