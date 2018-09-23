#include "headers.h"

struct utsname uinfo;
char present_dir[3][500];
job jobs[100];
job fore[100];
int job_c = 0, fore_c = 0, curid = 0;
int mode;

char *replace_str(char *str, char *orig, char *rep)
{
    static char buffer[4096];
    char *p;

    if (!(p = strstr(str, orig)))
        return str;

    strncpy(buffer, str, p - str);
    buffer[p - str] = '\0';

    sprintf(buffer + (p - str), "%s%s", rep, p + strlen(orig));

    return buffer;
}

void print()
{
    char *cwd = (char *)malloc(sizeof(char) * 1024);
    cwd = getcwd(cwd, 1024);
    char *s = replace_str(cwd, present_dir[2], "~");
    printf("<%s%s@%s%s:%s%s%s>", "\x1B[1;34m", uinfo.nodename, uinfo.sysname, "\x1B[0m", "\x1B[1;32m", s, "\x1B[0m");
    free(cwd);
}

int check_redirection(char *token)
{
    int i;
    int l = strlen(token);
    for (i = 0; i < l; i++)
    {
        if (token[i] == '<' || (token[i] == '>' && token[i + 1] != '>'))
            return 2;
        if (token[i] == '>' && token[i + 1] == '>')
            return 3;
    }
    return 0;
}

int check_pipe(char * token)
{
    int i;
    int l = strlen(token);
    for (i=0; i<l; i++)
    {
        if (token[i] == '|')
        return 1;
    }
    return 0;
}

void child_sig(int signo)
{
    pid_t pid;
    int x;
    pid = waitpid(WAIT_ANY, &x, WNOHANG);
    int i;
    for (i = 1; i <= job_c; i++)
    {
        if (jobs[i].pid == pid && jobs[i].state == 1)
        {
            int exit_status = WEXITSTATUS(x);
            jobs[i].state = 0;
            if (exit_status == 0)
                printf("\n%s with pid %d exited normally\n", jobs[i].name, jobs[i].pid);
            else
                printf("\n%s with pid %d exited with exit status %d\n", jobs[i].name, jobs[i].pid, exit_status);
            print();
            fflush(stdout);
            break;
        }
    }
}

void sig_handler(int signo)
{
    int i;
    for (i=1; i<=fore_c; i++)
    {
        if (fore[i].state == 1)
        {
            kill(fore[i].pid, 9);
            fore[i].state = 0;
            job_c++;
            jobs[job_c].state = fore[i].state;
            jobs[job_c].pid = fore[fore_c].pid;
            strcpy(jobs[job_c].name, fore[fore_c].name);
        }
    }
    signal(SIGTSTP, sig_handler);
}

int main()
{
    int errno = 0;
    if (uname(&uinfo) != 0)
    {
        perror("uname");
        exit(EXIT_FAILURE);
    }

    char *cwd = (char *)malloc(sizeof(char) * 1024);
    cwd = getcwd(cwd, 1024);

    strcpy(present_dir[0], uinfo.nodename);
    strcpy(present_dir[1], uinfo.sysname);
    strcpy(present_dir[2], cwd);

    free(cwd);

    print();

    signal(SIGCHLD, SIG_IGN);
    signal(SIGCHLD, child_sig);
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    //signal(SIGTSTP, sig_handler);

    while (1)
    {
        char *com;
        char *token_arr[200];
        ssize_t size = 0;
        getline(&com, &size, stdin);
        if (strcmp(com, "\n") == 0)
        {
            print();
            continue;
        }
        int i = 0, j = 0;
        token_arr[j] = strtok(com, ";");
        while (token_arr[j] != NULL)
        {
            j++;
            token_arr[j] = strtok(NULL, ";");
        }
        for (i = 0; i < j; i++)
        {
            char *token;
            char st[100][100];

            int c = check_pipe(token_arr[i]);
            if (c == 1)
            {
                execute_pipe(token_arr[i]);
                continue;
            }
            c = check_redirection(token_arr[i]);
            if (c == 2 || c == 3)
            {
                redirection(token_arr[i], (c - 2));
                continue;
            }

            token = strtok(token_arr[i], " \n\t\r");
            if (token == NULL)
                continue;

            if (strcmp(token, "quit") == 0)
                exit(0);
            else if (strcmp(token, "cd") == 0)
                cd(token, present_dir[2]);
            else if (strcmp(token, "pwd") == 0)
                pwd();
            // else if (strcmp(token, "echo") == 0)
            //     echo(token);
            else if (strcmp(token, "ls") == 0)
                ls(token, present_dir[2]);
            else if (strcmp(token, "pinfo") == 0)
                pinfo(token, present_dir[2]);
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
                int k = 0;
                while (token != NULL)
                {
                    strcpy(st[k++], token);
                    token = strtok(NULL, " \n\t\r");
                }
                if (strcmp(st[k - 1], "&") == 0)
                    background_process(st, k);
                else if (strcmp(st[0], "echo") == 0)
                    echo(st, k);
                else if (strcmp(st[0], "setenv") == 0)
                    set_env(st, k);
                else if (strcmp(st[0], "unsetenv") == 0)
                    unset_env(st, k);
                else if (strcmp(st[0], "kjob") == 0)
                    kjob(st);
                else if (strcmp(st[0], "fg") == 0)
                    fg(st);
                else if (strcmp(st[0], "bg") == 0)
                    bg(st);
                else
                    foreground(st, k);
            }
        }
        print();
        free(com);
    }
}