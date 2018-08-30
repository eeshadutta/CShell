#include "headers.h"

void printall(char *file, char *c)
{
    struct stat file_stat;
    struct group *gr;
    struct passwd *pwd;
    char path[100];
    strcpy(path, file);
    strcat(path, "/");
    strcat(path, c);
    if (stat(path, &file_stat) < 0)
        return;

    gr = getgrgid(file_stat.st_gid);
    pwd = getpwuid(file_stat.st_uid);

    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf(" ");
    printf("%ld ", file_stat.st_nlink);
    printf("%s ", pwd->pw_name);
    printf("%s ", gr->gr_name);
    printf(" %ld\t", file_stat.st_size);
    printf(" %.16s ", ctime(&file_stat.st_mtime));
    printf("%s\n", c);
}

void print_ls(char file[], int flag)
{
    struct dirent **file_list;
    int n = scandir(file, &file_list, NULL, alphasort);
    int i;
    if (flag == 0) // no flag
    {
        for (i = 0; i < n; i++)
        {
            if (file_list[i]->d_name[0] != '.')
                printf("%s\t", file_list[i]->d_name);
        }
        printf("\n");
    }
    else if (flag == 1) // -l flag
    {
        for (i = 0; i < n; i++)
        {
            if (file_list[i]->d_name[0] != '.')
                printall(file, file_list[i]->d_name);
        }
    }
    else if (flag == 2) // -a flag
    {
        for (i = 0; i < n; i++)
        {
            printf("%s\t", file_list[i]->d_name);
        }
        printf("\n");
    }
    else if (flag == 3) // -al or -la flag
    {
        for (i = 0; i < n; i++)
        {
            printall(file, file_list[i]->d_name);
        }
    }
}

void ls(char *token, char *present_dir)
{
    token = strtok(NULL, " \n\t\r");
    if (token == NULL)
        print_ls(".", 0);
    else if (strcmp(token, "-l") == 0)
    {
        token = strtok(NULL, " \n\t\r");
        if (token == NULL)
            print_ls(".", 1);
        else if (strcmp(token, "-a") == 0)
        {
            token = strtok(NULL, "\n\t\r");
            if (token == NULL)
                print_ls(".", 3);
            else
            {
                if (token[0] == '~')
                {
                    static char buffer[4096];
                    char *p;
                    char *str = token;
                    char *orig = "~";
                    char *rep = present_dir;
                    p = strstr(str, orig);
                    strncpy(buffer, str, p - str);
                    buffer[p - str] = '\0';
                    sprintf(buffer + (p - str), "%s%s", rep, p + strlen(orig));
                    strcpy(token, buffer);
                }
                print_ls(token, 3);
            }
        }
        else
        {
            print_ls(token, 1);
        }
    }
    else if (strcmp(token, "-a") == 0)
    {
        token = strtok(NULL, " \n\t\r");
        if (token == NULL)
            print_ls(".", 2);
        else if (strcmp(token, "-l") == 0)
        {
            token = strtok(NULL, " \n\t\r");
            if (token == NULL)
                print_ls(".", 3);
            else
            {
                if (token[0] == '~')
                {
                    static char buffer[4096];
                    char *p;
                    char *str = token;
                    char *orig = "~";
                    char *rep = present_dir;
                    p = strstr(str, orig);
                    strncpy(buffer, str, p - str);
                    buffer[p - str] = '\0';
                    sprintf(buffer + (p - str), "%s%s", rep, p + strlen(orig));
                    strcpy(token, buffer);
                }
                print_ls(token, 3);
            }
        }
        else
            print_ls(token, 2);
    }
    else if (strcmp(token, "-al") == 0 || strcmp(token, "-la") == 0)
    {
        token = strtok(NULL, " \n\t\r");
        if (token == NULL)
            print_ls(".", 3);
        else
        {
            if (token[0] == '~')
            {
                static char buffer[4096];
                char *p;
                char *str = token;
                char *orig = "~";
                char *rep = present_dir;
                p = strstr(str, orig);
                strncpy(buffer, str, p - str);
                buffer[p - str] = '\0';
                sprintf(buffer + (p - str), "%s%s", rep, p + strlen(orig));
                strcpy(token, buffer);
            }
            print_ls(token, 3);
        }
    }
    else
    {
        if (token[0] == '~')
        {
            static char buffer[4096];
            char *p;
            char *str = token;
            char *orig = "~";
            char *rep = present_dir;
            p = strstr(str, orig);
            strncpy(buffer, str, p - str);
            buffer[p - str] = '\0';
            sprintf(buffer + (p - str), "%s%s", rep, p + strlen(orig));
            strcpy(token, buffer);
        }
        print_ls(token, 0);
    }
}