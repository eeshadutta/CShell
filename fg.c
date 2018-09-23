#include "headers.h"

void fg(char buff[][100])
{
    int proc = atoi(buff[1]);
    if (proc > job_c)
    {
        printf("No such job exists\n");
        return;
    }
    if (jobs[proc].state == 1)
    {
        jobs[proc].state = 0;
        printf("%s\n", jobs[proc].name);
        int s;
        waitpid(jobs[proc].pid, &s, 0);
        fore_c++;
        strcpy(fore[fore_c].name, jobs[proc].name);
        fore[fore_c].pid = jobs[proc].pid;
        fore[fore_c].state = jobs[proc].state;
    }
    else
    {
        printf("%s\n", jobs[proc].name);
        int pid = fork();
        if (pid == 0)
        {
            pid_t proc_id = getpid();
            setpgid(proc_id, jobs[proc].pid);
            int k = 0, i;
            char st[100][100];
            char *temp = strtok(jobs[proc].name, " \n\t\r");
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
            fore_c++;
            strcpy(fore[fore_c].name, jobs[proc].name);
            fore[fore_c].pid = jobs[proc].pid;
            fore[fore_c].state = jobs[proc].state;
            while (wait(&status) != pid)
                ;
        }
    }
}