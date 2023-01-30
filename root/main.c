#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int main()
{
    char cmd[50];
    scanf("%s",cmd);
    
    while(1)
    {
        if(strcmp(cmd, "createfile") == 0)
        {

        }
        if(strcmp(cmd, "exit") == 0)
        {
            break;
        }
    }
}