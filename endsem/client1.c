#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/stat.h>
int main()
{
    int s, r, recb, sntb, x, i;
    printf("INPUT port number: ");
    scanf("%d", &x);
    struct sockaddr_in server;
    //char buff[50];
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
    {
        printf("\nSocket creation error.");
        exit(0);
    }
    printf("\nSocket created.");

    server.sin_family = AF_INET;
    server.sin_port = htons(x);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    r = connect(s, (struct sockaddr *)&server, sizeof(server));
    if (r == -1)
    {
        printf("\nConnection error.");
        exit(0);
    }
    printf("\nSocket connected.");
    char username[50], password[50], temp[50], validation[50], buff[100];
    printf("Enter Username: ");
    scanf(" %[^\n]", username);
    //fflush(stdin);
    printf("\n");
    printf("Enter Password: ");

    scanf(" %[^\n]", password);
    sprintf(buff, "%s\n%s\n", username, password);
    sntb = send(s, buff, sizeof(buff), 0);
    if (sntb == -1)
    {
        close(s);
        printf("\nMessage Sending Failed");
        exit(0);
    }
    int rcvb;
    rcvb = recv(s, buff, sizeof(buff), 0);
    puts(buff);
    close(s);
}