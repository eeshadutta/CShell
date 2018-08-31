#include "headers.h"

void clock_display(char *token)
{
    char st[100][100];
    int k = 0;
    while (token != NULL)
    {
        strcpy(st[k++], token);
        token = strtok(NULL, " \n\t\r");
    }
    int rem = atoi(st[2]);

    char d[40], t[40];
    strcpy(d, "/sys/class/rtc/rtc0/date");
    strcpy(t, "/sys/class/rtc/rtc0/time");
    while (1)
    {
        FILE *fp = fopen(d, "r");
        char dinfo[100], tinfo[100];
        fgets(dinfo, sizeof d, fp);
        int l = strlen(dinfo);
        dinfo[l - 1] = '\0';
        printf("%s, ", dinfo);
        fclose(fp);

        fp = fopen(t, "r");
        fgets(tinfo, sizeof t, fp);
        l = strlen(tinfo);
        tinfo[l - 1] = '\0';
        printf(" %s\n", tinfo);
        fclose(fp);

        sleep(rem);
    }
}