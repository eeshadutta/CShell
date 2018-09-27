#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <poll.h>
#include <syslog.h>

typedef struct job
{
    char name[100];
    int pid;
    //int state;
    int is_back;
} job;

extern job back[100];
extern job fore;
extern int back_count;
extern pid_t shellid;
extern pid_t childpid;
extern char present_dir[3][500];

void cd(char *token, char *home_dir);
void pwd();
void echo(char buff[][100], int k);
void ls(char *token, char *home_dir);
void background_process(char buff[][100], int k);
void foreground(char buff[][100], int k);
void pinfo(char *token, char *home_dir);
void remindme(char *token);
void clock_display(char *token);
void redirection(char *buff, int type);
void execute_pipe(char *buff);
void set_env(char buff[][100], int k);
void unset_env(char buff[][100], int k);
void print_jobs();
void kjob(char buff[][100]);
void fg(char buff[][100], int k);
void bg(char buff[][100], int k);
void overkill();