#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <arpa/inet.h>
#define MAXSIZE 50

int main()
{
    int sockfd, retval;
    char buff[MAXSIZE];
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;
    /**
        struct sockaddr_in {
        short int            sin_family;
        unsigned short int   sin_port;
        struct in_addr       sin_addr;
        unsigned char        sin_zero[8];
        };
     **/
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); //returns non negative value on connection
    if (sockfd == -1)
    {
        printf("\nSocket Creation Error");
        return 0;
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);                   // Host to Network ShortHost to Network Short
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //convert the string pointed to by cp, in the standard IPv4 dotted decimal notation

    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(3389);
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    retval = bind(sockfd, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
    if (retval == 1)
    {
        printf("Binding error");
        close(sockfd);
    }

    while (1)
    {
        printf("Enter a string: \n");
        scanf("%s", buff);

        sentbytes = sendto(sockfd, buff, sizeof(buff), 0,
                           (struct sockaddr *)&serveraddr, sizeof(serveraddr));

        if (sentbytes == -1)
        {
            printf("sending error");
            close(sockfd);
        }

        if ((buff[0] == 'H' || buff[0] == 'h') && buff[1] == 'a' && buff[2] == 'l' && buff[3] == 't')
        {
            break;
        }
        int size = sizeof(serveraddr);
        recedbytes = recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&serveraddr, &size);
        puts(buff);
        printf("\n");

        if ((buff[0] == 'H' || buff[0] == 'h') && buff[1] == 'a' && buff[2] == 'l' && buff[3] == 't')
        {
            break;
        }
    }
    close(sockfd);
}
