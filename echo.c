#include "headers.h"

void echo(char buff[][100], int k)
{
    int i;
    int lk = strlen(buff[(k - 1)]);
    int flag = 0;

    for (i = 1; i < k; i++)
    {
        int j;
        int l = strlen(buff[i]);
        for (j = 0; j < l; j++)
        {
            if (buff[i][j] == '\"' || buff[i][j] == '\'')
                flag = 1;
        }
    }
    if (buff[1][0] == '\"' && buff[(k - 1)][(lk - 1)] == '\"' || buff[1][0] == '\'' && buff[(k - 1)][(lk - 1)] == '\'')
        flag = 0;

    if (flag == 1)
    {
        printf("Invalid string\n");
        return;
    }

    for (i = 1; i < k; i++)
    {
        if (buff[i][0] == '$')
        {
            char *e = getenv(buff[i] + 1);
            if (e != NULL)
                printf("%s ", e);
        }
        else
        {
            int j;
            int l = strlen(buff[i]);
            for (j = 0; j < l; j++)
            {
                if (buff[i][j] != '\"' || buff[i][j] != '\'')
                printf ("%c", buff[i][j]);
            }
            printf (" ");
        }
    }
    printf ("\n");
    return;
}