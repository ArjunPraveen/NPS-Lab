#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp;
    fp = fopen("hello.txt", "a");
    fprintf(fp, "Indian Institute of Technology\nHarvard University");
    fclose(fp);
}