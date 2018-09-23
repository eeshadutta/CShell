#include "headers.h"

void redirection(char *buf, int type)
{
    char *op[2];
    char *ip[2];
    char *temp;
    char *temp2;
    char st[100][100];
    int i, k = 0, pid, status, in, out;

    op[0] = strtok(buf, ">");
    op[1] = strtok(NULL, ">");

    ip[0] = strtok(op[0], "<");
    ip[1] = strtok(NULL, "<");

    temp = strtok(ip[0], " \n\t\r");
    while (temp != NULL)
    {
        strcpy(st[k++], temp);
        temp = strtok(NULL, " \n\t\r");
    }

    char *com[k + 1];
    for (i = 0; i < k; i++)
        com[i] = st[i];
    com[i] = NULL;

    pid = fork();
    if (ip[1] != NULL)
    {
        temp2 = strtok(ip[1], " \n\t\r");
        if (temp2 != NULL)
        {
            in = open(temp2, O_RDONLY);
            if (pid == 0)
            {
                if (in >= 0)
                    dup2(in, 0);
                else
                {
                    printf("File does not exist\n");
                    return;
                }
            }
        }
        else
        {
            if (pid == 0)
            {
                printf("Invalid input file\n");
                exit(0);
            }
        }
    }
    if (op[1] != NULL)
    {
        temp2 = strtok(op[1], " \n\t\r");
        if (temp2 != NULL)
        {
            if (type == 0)
            out = open(temp2, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
            else 
            out = open(temp2, O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
            if (pid == 0)
            {
                dup2(out, 1);
            }
        }
        else
        {
            if (pid == 0)
            {
                printf("Invalid output file\n");
                exit(0);
            }
        }
    }
    if (pid == 0)
    {
        execvp(com[0], com);
        exit(0);
    }
    else
    {
        while (wait(&status) != pid)
            ;
    }
    return;
}
