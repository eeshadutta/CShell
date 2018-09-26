#include "headers.h"

void bg(char buff[][100])
{
    int proc = atoi(buff[1]);
    back[proc].state = 1;
    int pid = fork();
    childpid = pid;
    if (pid == 0)
    {
        pid_t proc_id = getpid();
        setpgid(0, 0);
        back[proc].pid = proc_id;
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
        
        execvp(com[0], com);
    }
    else 
    {
        back[proc].pid = pid;
    }
}