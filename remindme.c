#include "headers.h"

void remindme(char *token)
{
    char st[100][100];
    int k = 0;
    while (token != NULL)
    {
        strcpy(st[k++], token);
        token = strtok(NULL, " \n\t\r");
    }
    int i = 0;
    int rem = atoi(st[1]);

    int pid = fork();
    if (pid < 0)
        printf("Sorry reminder could not be added\n");
    else if (pid == 0)
    {
        sleep(rem);
        printf("\nREMINDER: ");
        for (i = 2; i < k; i++)
        {
            int l = strlen(st[i]);
            if (st[i][0] == '\"')
            {
                int j;
                for (j = 1; j < l; j++)
                    st[i][j - 1] = st[i][j];
                st[i][l - 1] = '\0';
            }
            l = strlen(st[i]);
            if (st[i][l - 1] == '\"')
            {
                st[i][l - 1] = '\0';
            }
            printf("%s ", st[i]);
        }
        printf("\n");
    }
    else
    {
        return;
    }
}