#include "headers.h"

int check_op(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '>')
            return 1;
        i++;
    }
    return 0;
}

int check_ip(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '<')
            return 1;
        i++;
    }
    return 0;
}

void execute_pipe(char *buff)
{
    char ***commands = (char ***)malloc(sizeof(char **) * 50);
    char *com;
    char *end;
    int num_com = 0;
    com = strtok_r(buff, "|", &end);
    int i = 0, j;
    while (com != NULL)
    {
        j = 0;
        char *token;
        char *end_tok;
        commands[i] = (char **)malloc(sizeof(char *) * 50);
        token = strtok_r(com, " \n\t\r", &end_tok);
        while (token != NULL)
        {
            commands[i][j] = (char *)malloc(sizeof(char) * 50);
            strcpy(commands[i][j], token);
            token = strtok_r(NULL, " \n\t\r", &end_tok);
            j++;
        }
        commands[i][j] = NULL;
        num_com++;
        com = strtok_r(NULL, "|", &end);
        i++;
    }
    commands[i] = NULL;

    int p = 0;
    int fd[2];
    int fd_in = 0;
    pid_t pid;

    while (*commands != NULL)
    {
        pipe(fd);
        pid = fork();
        if (pid == -1)
        {
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            dup2(fd_in, 0);
            if (p != (num_com - 1))
                dup2(fd[1], 1);
            close(fd[0]);
            if (check_ip((*commands)[0]))
            {
                char *ip[2];
                char *temp;
                char st[100][100];
                int k = 0;
                ip[0] = strtok((*commands)[0], "<");
                ip[1] = strtok(NULL, "<");

                temp = strtok(ip[0], " \n\t\r");
                while (temp != NULL)
                {
                    strcpy(st[k++], temp);
                    temp = strtok(NULL, " \n\t\r");
                }

                char *cmd[k + 1];
                for (i = 0; i < k; i++)
                    cmd[i] = st[i];
                cmd[i] = NULL;

                char *t = strtok(ip[1], " \n\t\r");
                if (t != NULL)
                {
                    int in = open(t, O_RDONLY);
                    if (in < 0)
                    {
                        printf("File does not exist\n");
                        return;
                    }
                    else
                        dup2(in, 0);
                }
                execvp(cmd[0], cmd);
            }
            if (check_op((*commands)[0]))
            {
                char *op[2];
                char *temp;
                char st[100][100];
                int k = 0;
                op[0] = strtok((*commands)[0], ">");
                op[1] = strtok(NULL, ">");

                temp = strtok(op[0], " \n\t\r");
                while (temp != NULL)
                {
                    strcpy(st[k++], temp);
                    temp = strtok(NULL, " \n\t\r");
                }

                char *cmd[k + 1];
                for (i = 0; i < k; i++)
                    cmd[i] = st[i];
                cmd[i] = NULL;

                char *t = strtok(op[1], " \n\t\r");
                if (t != NULL)
                {
                    int out = open(t, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
                    dup2(out, 1);
                    execvp(cmd[0], cmd);
                }
            }
            else
                execvp((*commands)[0], *commands);
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
            close(fd[1]);
            fd_in = fd[0];
            commands++;
            p++;
        }
    }
}