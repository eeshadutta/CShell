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

void cd(char *token, char *home_dir);
void pwd();
void echo(char *str);
void ls(char *token);
void background_process(char st[][100], int k);
void foreground(char st[][100], int k);
void pinfo(char *token);