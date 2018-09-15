#include "headers.h"

// void echo(char *str)
// {
//     char *s = (char *)malloc(sizeof(char) * 1024);
//     int i = 5, f = 0;
//     while (str[i] != '\n')
//         s[f++] = str[i++];
//     s[f] = '\0';
//     if (f == 0)
//     {
//         printf("\n");
//         return;
//     }
//     char *token;
//     if ((strcmp(s, "\'") == 0) || (strcmp(s, "\"") == 0))
//     {
//         printf("invalid string\n");
//         return;
//     }
//     if ((strcmp(s, "\'\'") == 0) || (strcmp(s, "\"\"") == 0))
//     {
//         printf("\n");
//         return;
//     }

//     i = 0;
//     while (s[i] == ' ')
//         i++;
//     int j = i;
//     while (s[j] != '\0')
//         j++;
//     j--;

//     if ((s[i] != '\"') && (s[i] != '\'') && (s[j] != '\"') && (s[j] != '\''))
//     {
//         token = strtok(s, " ");
//         while (token != NULL)
//         {
//             printf("%s ", token);
//             token = strtok(NULL, " ");
//         }
//     }
//     else
//     {
//         while(s[j] == ' ') j--;
//         while ((s[i] == '\"' && s[j] == '\"') || (s[i] == '\'' && s[j] == '\''))
//         {
//             i++;
//             j--;
//         }
//         if (s[i] == '\"' || s[i] == '\'' || s[j] == '\"' || s[j] == '\'')
//         {
//             printf("invalid string\n");
//             return;
//         }
//         j++;
//         while (i != j)
//         {
//             printf("%c", s[i]);
//             i++;
//         }
//     }
//     printf("\n");
//     free(s);
//     return;
// }

void echo(char buff[][100], int k)
{
    int i;
    int lk = strlen(buff[(k - 1)]);
    int flag = 0;

    for (i = 1; i < k; i++)
    {
        int j;
        int l = strlen(buff[i]);
        for (j = 0; j < l; j++)
        {
            if (buff[i][j] == '\"' || buff[i][j] == '\'')
                flag = 1;
        }
    }
    if (buff[1][0] == '\"' && buff[(k - 1)][(lk - 1)] == '\"' || buff[1][0] == '\'' && buff[(k - 1)][(lk - 1)] == '\'')
        flag = 0;

    if (flag == 1)
    {
        printf("Invalid string\n");
        return;
    }

    for (i = 1; i < k; i++)
    {
        if (buff[i][0] == '$')
        {
            char *e = getenv(buff[i] + 1);
            if (e != NULL)
                printf("%s ", e);
        }
        else
        {
            int j;
            int l = strlen(buff[i]);
            for (j = 0; j < l; j++)
            {
                if (buff[i][j] != '\"' || buff[i][j] != '\'')
                printf ("%c", buff[i][j]);
            }
            printf (" ");
        }
    }
    printf ("\n");
    return;
}