#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd[2]; 
    if (pipe(fd) < 0)
    {
        printf("create pipe failed...\n");
        return -1;
    }
 
    char *temp = "yuki";
    if (write(fd[0], temp, strlen(temp) + 1) < 0)
    {
        printf("write pipe failed...\n");
    }
 
    return 0;
}

