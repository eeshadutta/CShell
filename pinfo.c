#include "headers.h"

void pinfo(char *token, char *home_dir)
{
    char stat[1000];
    char exec[1000];
    int c = 0;
    char st[100][100];
    while (token != NULL)
    {
        strcpy(st[c++], token);
        token = strtok(NULL, " \n\t\r");
    }
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
        strcpy(stat, "/proc/");
        strcat(stat, buff);
        strcat(stat, "/stat");
        strcpy(exec, "/proc/");
        strcat(exec, buff);
        strcat(exec, "/exe");
    }
    FILE *fd;
    if ((fd = fopen(stat, "r")) == NULL)
        printf("Error: Process desn't exist\n");
    else
    {
        int pid;
        char status;
        long unsigned memory;
        char path[1000];
        fscanf(fd, "%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &pid, &status, &memory);
        fclose(fd);
        printf("pid -- %d\n", pid);
        printf("Process Status -- %c\n", status);
        printf("Memory -- %lu\n", memory);

        int nb = readlink(exec, path, 1000);
        path[nb] = '\0';

        char *p;
        char *str = path;
        char *orig = home_dir;
        char *rep = "~";
        static char buffer[4096];
        if (p = strstr(str, orig))
        {
            strncpy(buffer, str, p - str);
            buffer[p - str] = '\0';
            sprintf(buffer + (p-str), "%s%s", rep, p + strlen(orig));
            strcpy(path, buffer);
        }
        printf("Executable Path -- %s\n", path);
    }
}