#include "headers.h"

void pwd()
{
    char *cwd = (char *)malloc(sizeof(char) * 1024);
    cwd = getcwd(cwd, 1024);
    printf("%s\n", cwd);
    free(cwd);
    return;
}