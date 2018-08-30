#include "headers.h"
#include "variables.h"

struct utsname uinfo;
char present_dir[3][500];
bcg background[100];
int back_c=0,curid=0; 
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
            token = strtok(token_arr[i], " \n\t\r");
            if (token == NULL)
                continue;

            if (strcmp(token, "quit") == 0)
                return 0;
            else if (strcmp(token, "cd") == 0)
                cd(token, present_dir[2]);
            else if (strcmp(token, "pwd") == 0)
                pwd();
            else if (strcmp(token, "echo") == 0)
                echo(token);
            else if (strcmp(token, "ls") == 0)
                ls(token);
            else if (strcmp(token, "pinfo") == 0)
                pinfo(token);
            else
            {
                int k = 0;
                while (token != NULL)
                {
                    strcpy (st[k++], token);
                    token = strtok(NULL, " \n\t\r");
                }
                if (strcmp(st[k-1], "&") == 0)
                    background_process(st, k);
                else    
                    foreground(st, k);
            }
        }
        print();
        free(com);
    }
}