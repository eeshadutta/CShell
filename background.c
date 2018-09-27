#include "headers.h"

void background_process(char st[100][100], int k)
{
    char *com[k + 1];
    int i = 0;
    for (i = 0; i < k; i++)
    {
        com[i] = st[i];
    }
    com[i] = NULL;

    int pid = fork();
    childpid = pid;

    if (pid < 0)
    {
        printf("Error: Fork Failed\n");
        return;
    }
    else if (pid == 0)
    {
        setpgid(0, 0);
        execvp(com[0], com);
    }
    else
    {
        back_count++;
        printf("[%d] %d\n", back_count, pid);
    }

    char name[100];
    strcpy(name, com[0]);
    for (i = 1; i < (k - 1); i++)
    {
        strcat(name, " ");
        strcat(name, st[i]);
    }

    back[back_count].pid = pid;
    back[back_count].is_back = 1;
    strcpy(back[back_count].name, name);
    return;
}