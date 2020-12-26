#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp;
    fp = fopen("hello.txt", "r");
    char buff[200];
    while (fscanf(fp, "%s", buff) != EOF)
    {
        printf("%s\n", buff);
    }
    puts(buff);
    fclose(fp);
}