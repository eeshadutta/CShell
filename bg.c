#include "headers.h"

void bg(char buff[][100], int k)
{
    int proc = atoi(buff[1]);
    if (k >= 3) 
        printf("Too many arguments\n");
    else if (k <= 1)
        printf("Too few arguments\n");
    else 
    {
        if (proc > back_count)
            printf("No such job\n");
        else 
        {
            pid_t pid = back[proc].pid;
            kill(pid, SIGTTIN);
            kill(pid, SIGCONT);
        }
    }
}