#include "headers.h"

void overkill()
{
    int i;
    for (i=1; i<=job_c; i++)
    {
        if (jobs[i].state == 1)
        {
            kill(jobs[i].pid, 9);
            jobs[i].state = 0;
        }
    }
}