#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp;
    fp = fopen("usernames.txt", "r");

    char username[50], password[50], temp[50], validation[50];
    printf("Enter Username: ");
    scanf(" %[^\n]", username);
    //fflush(stdin);
    printf("\n");
    printf("Enter Password: ");

    scanf(" %[^\n]", password);
    //fflush(stdin);
    int line = 0, userline, check;

    if (fp == NULL)
        printf("File not found");

    else
    {
        //puts(username);
        while (fgets(temp, 50, fp) != NULL)
        {
            line++;
        }
        int total_lines = line, len;
        line = 0;
        fp = fopen("usernames.txt", "r");
        while (fgets(temp, 50, fp) != NULL)
        {
            len = strlen(temp);
            if (len > 0 && temp[len - 1] == '\n')
                temp[len - 1] = '\0';
            check = strcmp(temp, username);
            //puts(temp);
            if (check == 0)
            {
                userline = line + 1;
                break;
            }
            line++;
        }
        //printf("%d %d", line, total_lines);
        if (line == total_lines)
        {
            strcpy(validation, "User not found\0");
        }

        line = 0;
        fp = fopen("usernames.txt", "r");
        while (fgets(temp, 50, fp) != NULL)
        {
            if (line == userline)
            {
                len = strlen(temp);
                if (len > 0 && temp[len - 1] == '\n')
                    temp[len - 1] = '\0';

                check = strcmp(temp, password);
                if (check == 0)
                {
                    strcpy(validation, "Validated!\n");
                }
                else
                {
                    strcpy(validation, "Wrong Password\n");
                }
            }
            line++;
        }
        printf("\n");
        puts(validation);
    }
}