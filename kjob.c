#include "headers.h"

void kjob(char buff[][100])
{
    int proc = atoi(buff[1]);
    int sig = atoi(buff[2]);
    if (proc > job_c)
    {
        printf ("No such job exists\n");
        return;
    }
    if (jobs[proc].state == 1)
        kill(jobs[proc].pid, sig);
    else 
        printf ("Stopped process\n");
}