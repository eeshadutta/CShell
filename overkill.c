#include "headers.h"

void overkill()
{
    int i;
    for (i=1; i<=back_count; i++)
    {
        if (back[i].state == 1)
        {
            kill(back[i].pid, 9);
            back[i].state = 0;
        }
    }
}