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
        int saved_stdout = dup(STDOUT_FILENO);

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
                char *token;
                token = strtok(cmd[0], " \n\t\r");
                if (strcmp(token, "cd") == 0)
                    cd(token, present_dir[2]);
                else if (strcmp(token, "pwd") == 0)
                    pwd();
                else if (strcmp(token, "pinfo") == 0)
                    pinfo(token, "pinfo");
                else if (strcmp(token, "remindme") == 0)
                    remindme(token);
                else if (strcmp(token, "clock") == 0)
                    clock_display(token);
                else if (strcmp(token, "jobs") == 0)
                    print_jobs();
                else if (strcmp(token, "overkill") == 0)
                    overkill();
                else
                {
                    if (execvp(cmd[0], cmd) == -1)
                    {
                        dup2(saved_stdout, 1);
                        printf("no such command\n");
                    }
                }
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

                    char *token;
                    token = strtok(cmd[0], " \n\t\r");
                    if (strcmp(token, "cd") == 0)
                        cd(token, present_dir[2]);
                    else if (strcmp(token, "pwd") == 0)
                        pwd();
                    else if (strcmp(token, "pinfo") == 0)
                        pinfo(token, "pinfo");
                    else if (strcmp(token, "remindme") == 0)
                        remindme(token);
                    else if (strcmp(token, "clock") == 0)
                        clock_display(token);
                    else if (strcmp(token, "jobs") == 0)
                        print_jobs();
                    else if (strcmp(token, "overkill") == 0)
                        overkill();
                    else
                    {
                        if (execvp(cmd[0], cmd) == -1)
                        {
                            dup2(saved_stdout, 1);
                            printf("no such command\n");
                        }
                    }
                }
            }
            else
            {
                char *token;
                token = strtok((*commands)[0], " \n\t\r");
                if (strcmp(token, "cd") == 0)
                    cd(token, present_dir[2]);
                else if (strcmp(token, "pwd") == 0)
                    pwd();
                else if (strcmp(token, "pinfo") == 0)
                    pinfo(token, "pinfo");
                else if (strcmp(token, "remindme") == 0)
                    remindme(token);
                else if (strcmp(token, "clock") == 0)
                    clock_display(token);
                else if (strcmp(token, "jobs") == 0)
                    print_jobs();
                else if (strcmp(token, "overkill") == 0)
                    overkill();
                else
                {
                    if (execvp((*commands)[0], *commands) == -1)
                    {
                        dup2(saved_stdout, 1);
                        printf("no such command\n");
                    }
                }
            }
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