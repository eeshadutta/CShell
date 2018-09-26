#include "headers.h"

void kjob(char buff[][100])
{
    int proc = atoi(buff[1]);
    int sig = atoi(buff[2]);
    if (proc > back_count)
    {
        printf ("No such job exists\n");
        return;
    }
    if (back[proc].state == 1)
        kill(back[proc].pid, sig);
    else 
        printf ("Stopped process\n");
}