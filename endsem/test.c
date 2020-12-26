
#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fileptr;
    char manipal[] = "Manipal Institute of Technology";
    fileptr = fopen("hello.txt", "w");
    if (fileptr == NULL)
    {
        printf("File not opening");
        printf("\n");
    }
    else
    {
        fputs(manipal, fileptr);
        fputs("\n", fileptr);
    }

    fclose(fileptr);
    return 0;
}