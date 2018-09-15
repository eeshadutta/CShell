#include "headers.h"

void bg(char buff[][100])
{
    int proc = atoi(buff[1]);
    jobs[proc].state = 1;
    int pid = fork();
    if (pid == 0)
    {
        pid_t proc_id = getpid();
        setpgid(proc_id, jobs[proc].pid);
        // jobs[proc].pid = proc_id;
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
        
        //kill(jobs[proc].pid, SIGCONT);
        execvp(com[0], com);
    }
    else 
    {
        printf("[%d] %d\n", proc, jobs[proc].pid);
    }
}