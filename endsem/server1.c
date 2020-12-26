#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int s, r, recb, sntb, x, ns, a = 0;
    printf("INPUT port number: ");
    scanf("%d", &x);
    socklen_t len;
    struct sockaddr_in server, client;
    char buff[50];

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
    {
        printf("\nSocket creation error.");
        exit(0);
    }
    printf("\nSocket created.");

    server.sin_family = AF_INET;
    server.sin_port = htons(x);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    r = bind(s, (struct sockaddr *)&server, sizeof(server));
    if (r == -1)
    {
        printf("\nBinding error.");
        exit(0);
    }
    printf("\nSocket binded.");

    r = listen(s, 1);
    if (r == -1)
    {
        close(s);
        exit(0);
    }
    printf("\nSocket listening.");

    len = sizeof(client);

    ns = accept(s, (struct sockaddr *)&client, &len);
    if (ns == -1)
    {
        close(s);
        exit(0);
    }
    printf("\nSocket accepting.");
    char arr[50];
    int arr1[50], arr2[50];
    recb = recv(ns, arr, sizeof(arr), 0);
    if (recb == -1)
    {
        printf("\nMessage Recieving Failed");
        close(s);
        close(ns);
        exit(0);
    }
    puts(arr);
    char username[50], password[50], temp[50], validation[50];
    int line = 0, userline, check;
    int i = 0;
    while (arr[i] != '\n')
    {
        if (arr[i] == '\n')
            break;
        username[i] = arr[i];
        i++;
    }
    username[i++] = '\0';
    int j = 0;
    while (arr[i] != '\n')
    {
        password[j++] = arr[i];
        i++;
    }
    password[j] = '\0';
    puts(username);
    puts(password);
    FILE *fp;
    fp = fopen("usernames.txt", "r");

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
        sntb = send(ns, validation, sizeof(validation), 0);
    }

    close(ns);
    close(s);
}
