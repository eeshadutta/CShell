#include "headers.h"

void print_jobs()
{
    int i;
    int j = 1;
    for (i = 1; i <= back_count; i++)
    {
        if (back[i].is_back == 1)
        {
            char stat[1000];
            char status;
            int p;
            long unsigned mem;
            char str[10];
            sprintf(str, "%d", back[i].pid);

            strcpy(stat, "/proc/");
            strcat(stat, str);
            strcat(stat, "/stat");
            FILE *fd;
            if ((fd = fopen(stat, "r")) == NULL)
            {
                printf("[%d] %s %s [%d]\n", j, "Done", back[i].name, back[i].pid);
            }
            else
            {
                fscanf(fd, "%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &p, &status, &mem);
                fclose(fd);
                printf("[%d] ", j);
                if (status == 'T')
                    printf("%s ", "Stopped");
                else 
                    printf("%s ", "Running");
                printf("%s [%d]\n", back[i].name, back[i].pid);
            }
            j++;
        }
    }
}