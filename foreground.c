#include "headers.h"

void foreground(char st[][100], int k)
{
    char *com[k + 1];
    int status;
    int i = 0;
    for (i = 0; i < k; i++)
    {
        com[i] = st[i];
    }
    com[i] = NULL;

    int pid = fork();
    if (pid < 0)
    {
        printf("Error: Fork Failed\n");
        return;
    }
    else if (pid == 0)
    {
        if (execvp(com[0], com) == -1)
        {
            printf("no such command\n");
            return;
        }
    }
    else
    {
        int x;
        shellid = pid;
        char name[100];
        strcpy(name, com[0]);
        for (i = 1; i < (k - 1); i++)
        {
            strcat(name, " ");
            strcat(name, st[i]);
        }

        fore.pid = pid;
        strcpy(fore.name, name);

        if (WIFSTOPPED(x))
        {
            fore.state = 1;
        }
        else
        {
            fore.state = 0;
        }
        while (wait(&status) != pid)
            ;
    }

    return;
}