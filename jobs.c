#include "headers.h"

void print_jobs()
{
    int i;
    for (i = 1; i <= back_count; i++)
    {
        if (strcmp(back[i].name, "") != 0)
        {
            if (back[i].state == 1)
                printf("[%d] %s %s [%d]\n", i, "Running", back[i].name, back[i].pid);
            else
                printf("[%d] %s %s [%d]\n", i, "Stopped", back[i].name, back[i].pid);
        }
    }
}