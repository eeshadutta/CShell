#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "echo.h"

void echo(char *str)
{
    char *s = (char *)malloc(sizeof(char)*1024);
    int i = 5, f = 0;
    while (str[i] != '\n')
        s[f++] = str[i++];
    s[f] = '\0';
    if (f == 0)
    {
        printf("\n");
        return;
    }
    char *token;
    if ((strcmp(s, "\'") == 0) || (strcmp(s, "\"") == 0))
    {
        printf("invalid string\n");
        return;
    }
    if ((strcmp(s, "\'\'") == 0) || (strcmp(s, "\"\"") == 0))
    {
        printf("\n");
        return;
    }

    i = 0;
    while (s[i] == ' ') i++;
    int j = i;
    while (s[j] != '\0') j++;
    j--;

    if ((s[i] != '\"') && (s[i] != '\'') && (s[j] != '\"') && (s[j] != '\''))
    {
        token = strtok(s, " ");
        while(token != NULL)
        {
            printf("%s ", token);
            token = strtok(NULL, " ");
        }
    }
    else
    {
        while ((s[i] == '\"' && s[j] == '\"') || (s[i] == '\'' && s[j] == '\''))
        {
            i++;
            j--;
        }
        if (s[i] == '\"' || s[i] == '\'' || s[j] == '\"' || s[j] == '\'') 
        {
            printf ("invalid string\n");
            return;
        }
        j++;
        while(i != j)
        {
            printf("%c", s[i]);
            i++;
        }
    }
    printf ("\n");
    free(s);
    return;
}