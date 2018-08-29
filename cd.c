#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "cd.h"

void cd(char *token, char *present_dir)
{
    token = strtok(NULL, " \n\t\r");
    if (token == NULL)
        chdir(present_dir);
    else if (token[0] == '~' && strlen(token) >= 1)
    {
        static char buffer[4096];
        char *p;
        char *str = token;
        char *orig = "~";
        char *rep = present_dir;
        p = strstr(str, orig);
        strncpy(buffer, str, p - str);
        buffer[p - str] = '\0';

        sprintf(buffer + (p - str), "%s%s", rep, p + strlen(orig));
        if (chdir(buffer) != 0)
            printf("directory doesn't exist\n");
    }
    else if (strcmp(token, "~") == 0)
        chdir(present_dir);
    else if (chdir(token) != 0)
        printf("directory doesn't exist\n");
    return;
}