#include "headers.h"

void fg(char buff[][100], int k)
{
    int proc = atoi(buff[1]);
    if (k >= 3)
        printf("Too many arguments\n");
    else if (k <= 1)
        printf("Too few arguments\n");
    else
    {
        if (proc > back_count)
            printf("No such job/n");
        else
        {
            pid_t pid = back[proc].pid;
            char stat[1000];
            char status;
            int p;
            long unsigned mem;
            char str[10];
            sprintf(str, "%d", back[proc].pid);

            strcpy(stat, "/proc/");
            strcat(stat, str);
            strcat(stat, "/stat");
            FILE *fd;
            if ((fd = fopen(stat, "r")) == NULL)
            {
                printf("Process has been terminated. Cannot bring to foreground.\n");
            }
            else
            {
                kill(pid, SIGCONT);
                childpid = pid;
                strcpy(fore.name, back[proc].name);
                fore.pid = back[proc].pid;
                fore.is_back = 0;
                int j = proc;
                for (j = proc; j < back_count; j++)
                {
                    back[j] = back[j + 1];
                }
                back_count--;
                waitpid(-1, NULL, WUNTRACED);
            }
        }
    }
}