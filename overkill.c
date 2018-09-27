#include "headers.h"

void overkill()
{
    int i;
    for (i = 1; i <= back_count; i++)
    {
        kill(back[i].pid, 9);
    }
}