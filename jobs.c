#include "headers.h"

void print_jobs()
{
    int i;
    for (i=1; i<=job_c; i++)
    {
        if (jobs[i].state == 1)
            printf ("[%d] %s %s [%d]\n", i, "Running", jobs[i].name, jobs[i].pid);
        else 
            printf ("[%d] %s %s [%d]\n", i, "Stopped", jobs[i].name, jobs[i].pid);            
    }
}