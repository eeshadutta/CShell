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

    if (pid < 0)
    {
        printf("Error: Fork Failed\n");
        return;
    }
    else if (pid == 0)
    {
        execvp(com[0], com);
    }
    else
    {
        job_c++;
        printf("[%d] %d\n", job_c, pid);
    }

    char name[100];
    strcpy(name, com[0]);
    for (i = 1; i < (k - 1); i++)
    {
        strcat(name, " ");
        strcat(name, st[i]);
    }

    jobs[job_c].pid = pid;
    jobs[job_c].state = 1;
    strcpy(jobs[job_c].name, name);
    return;
}