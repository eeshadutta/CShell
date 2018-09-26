#include "headers.h"

void fg(char buff[][100])
{
    int proc = atoi(buff[1]);
    if (proc > back_count)
    {
        printf("No such job exists\n");
        return;
    }
    if (back[proc].state == 1)
    {
        back[proc].state = 0;
        printf("%s\n", back[proc].name);
        int s;
        childpid = getpid();
        waitpid(back[proc].pid, &s, 0);
        strcpy(fore.name, back[proc].name);
        fore.pid = back[proc].pid;
        fore.state = back[proc].state;
        strcpy(back[proc].name, "");
    }
    else
    {
        printf("%s\n", back[proc].name);
        int pid = fork();
        if (pid == 0)
        {
            pid_t proc_id = getpid();
            childpid = proc_id;
            setpgid(proc_id, back[proc].pid);
            int k = 0, i;
            char st[100][100];
            char *temp = strtok(back[proc].name, " \n\t\r");
            while (temp != NULL)
            {
                strcpy(st[k++], temp);
                temp = strtok(NULL, " \n\t\r");
            }

            char *com[k + 1];
            for (i = 0; i < k; i++)
                com[i] = st[i];
            com[i] = NULL;

            if (execvp(com[0], com) == -1)
            {
                printf("no such command\n");
                return;
            }
        }
        else
        {
            int status;
            strcpy(fore.name, back[proc].name);
            fore.pid = back[proc].pid;
            fore.state = back[proc].state;
            strcpy(back[proc].name, "");
            while (wait(&status) != pid)
                ;
        }
    }
}