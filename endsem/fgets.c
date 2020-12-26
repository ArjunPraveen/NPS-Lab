#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp;
    char buff[50];
    fp = fopen("hello.txt", "r");
    if (fp == NULL)
        printf("File not opening");
    while (fgets(buff, 50, fp) != NULL)
    {
        puts(buff);
    }
    fclose(fp);
}