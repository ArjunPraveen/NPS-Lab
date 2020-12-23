#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_LEN 100

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
    printf("\nSocket listening.\n");

    len = sizeof(client);

    ns = accept(s, (struct sockaddr *)&client, &len);
    if (ns == -1)
    {
        close(s);
        exit(0);
    }
    printf("\nSocket accepting.\n");

    recb = recv(ns, buff, sizeof(buff), 0);
    if (recb == -1)
    {
        printf("\nMessage Recieving Failed");
        close(s);
        close(ns);
        exit(0);
    }

    printf("%s", buff);
    printf("\n\n");
    //scanf("%s", buff);

    char fil[50];
    if (access("hello.txt", F_OK) != -1)
    {
        // file exists

        printf("Validating Data\n");
    }
    else
    {
        // file doesn't exist
        printf("File not present\n");
    }
    int c = 0;
    char usr[50], pass[50];
    int i;
    for (i = 0; i < strlen(buff); i++)
    {
        if (buff[i] == ' ')
            break;

        usr[i] = buff[i];
    }
    usr[i] = '\0';
    int j;
    int k = 0;
    for (j = i + 1; j < strlen(buff); j++)
    {
        pass[k++] = buff[j];
    }
    pass[k] = '\0';
    printf("%s\n", usr);
    printf("%s\n", pass);
    int line_num = 1;
    int find_result = 0;
    int find_result1 = 0;
    char temp[512];
    FILE *fp;
    if ((fp = fopen("hello.txt", "r")) == NULL)
    {
        printf("\nFile not found");
        close(s);
        close(ns);
        exit(0);
    }
    while (fgets(temp, 512, fp) != NULL)
    {
        if ((strstr(temp, usr)) != NULL)
        {
            find_result++;
        }
        line_num++;
    }

    if ((fp = fopen("hello.txt", "r")) == NULL)
    {
        printf("\nFile not found");
        close(s);
        close(ns);
        exit(0);
    }
    while (fgets(temp, 512, fp) != NULL)
    {
        if ((strstr(temp, pass)) != NULL)
        {
            find_result1++;
        }
        break;
    }
    printf("%d %d", find_result, find_result1);
    if (find_result == 1 && find_result1 == 1)
    {
        printf("logged in");
        char check[] = "Logged in successfuly\nBalance: 3000";
        sntb = send(ns, check, sizeof(check), 0);
    }
    else if (find_result == 1 && find_result1 == 0)
    {
        //printf("logged in");
        char inusr[] = "Incorrect Password";
        sntb = send(ns, inusr, sizeof(inusr), 0);
    }
    else if (find_result == 0 && find_result1 == 1)
    {
        //printf("logged in");
        char inpass[] = "Incorrect Username";
        sntb = send(ns, inpass, sizeof(inpass), 0);
    }
    else
    {
        printf("logged fail");
        char fail[] = "Logged in successfuly";
        sntb = send(ns, fail, sizeof(fail), 0);
    }
}