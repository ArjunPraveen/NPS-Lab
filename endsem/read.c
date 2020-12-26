#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fileptr;
    fileptr = fopen("hello.txt", "r");
    char c;
    if (fileptr == NULL)
    {
        printf("File cannot be read");
    }
    else
    {
        while (1)
        {
            c = fgetc(fileptr);
            if (c == EOF)
                break;
            printf("%c", c);
        }
    }

    fclose(fileptr);
}