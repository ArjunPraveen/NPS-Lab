#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define MAXSIZE 90

int isPalindrome(char str[])
{

    int l = 0;
    int h = strlen(str) - 1;

    while (h > l)
    {
        if (str[l++] != str[h--])
            return 0;
    }
    //printf("Palindrome : True\n");
    return 1;
}

int main()
{
    int sockfd, newsockfd, retval, i;
    socklen_t actuallen;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;

    char buff[MAXSIZE];
    char output[MAXSIZE];
    int a = 0;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1)
    {
        printf("\nSocket creation error");
    }
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(3389);
    clientaddr.sin_addr.s_addr = htons(INADDR_ANY);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);

    retval = bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (retval == 1)
    {
        printf("Binding error");
        close(sockfd);
    }

    while (1)
    {

        actuallen = sizeof(clientaddr);
        recedbytes = recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&clientaddr, &actuallen);

        if (recedbytes == -1)
        {
            printf("Reciving error\n");
            close(sockfd);
        }

        puts(buff);
        printf("\n");

        if ((buff[0] == 'H' || buff[0] == 'h') && buff[1] == 'a' && buff[2] == 'l' && buff[3] == 't')
        {
            break;
        }
        int check = isPalindrome(buff);

        if (!check)
        {
            int i = 0; //start at 0
            char test[] = "Palindrome : False";
            puts(test);
            strcpy(output, test);
        }
        else
        {
            int i = 0, c = 0, count = 0; //start at 0
            char test[] = "Palindrome : True";
            puts(test);
            strcpy(output, test);
            char len[MAXSIZE], countstr[MAXSIZE], space[] = " ";
            sprintf(len, "%ld", strlen(buff));
            strcat(output, space);
            //puts(output );
            strcat(output, len);
            puts(output);
            while (buff[c] != '\0')
            {
                if (buff[c] == 'a' || buff[c] == 'A' || buff[c] == 'e' || buff[c] == 'E' || buff[c] == 'i' || buff[c] == 'I' || buff[c] == 'o' || buff[c] == 'O' || buff[c] == 'u' || buff[c] == 'U')
                    count++;
                c++;
            }
            sprintf(countstr, "%d", count);
            strcat(output, space);
            strcat(output, countstr);
        }

        //scanf("%s", buff);
        sentbytes = sendto(sockfd, output, sizeof(buff), 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
        if (sentbytes == -1)
        {
            printf("sending error");
            close(sockfd);
        }

        if ((buff[0] == 'H' || buff[0] == 'h') && buff[1] == 'a' && buff[2] == 'l' && buff[3] == 't')
        {
            break;
        }
    }

    close(sockfd);
    close(newsockfd);
}
