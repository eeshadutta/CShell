#include "headers.h"

void set_env(char buff[][100], int k)
{
    if (k == 3)
        setenv(buff[1], buff[2], 1);
    else if (k == 2)
        setenv(buff[1], " ", 1);
    else
    {
        printf("Only 2 arguments expected\n");
        return;
    }
    return;
}

void unset_env(char buff[][100], int k)
{
    if (k != 2)
    {
        printf("Only 1 argument expected\n");
        return;
    }
    unsetenv(buff[1]);
    return;
}