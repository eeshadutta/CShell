#include "headers.h"
#include "variables.h"

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
        while (wait(&status) != pid)
            ;
    }

    int x;
    curid = pid;
    char name[100];
    strcpy(name, com[0]);
    for (i = 1; i < (k - 1); i++)
    {
        strcat(name, " ");
        strcat(name, st[i]);
    }

    background[back_c].pi = pid;
    strcpy(background[back_c].name, name);

    if (WIFSTOPPED(x))
    {
        background[back_c].state = 1;
    }
    else
    {
        background[back_c].state = 0;
    }
    back_c++;
    return;
}