#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

void invalid_command(void)
{
    printf("invalid command!\n");
}

int main()
{
    char cmd[50];
    scanf("%s",cmd);
    
    while(strcmp(cmd, "exit"))
    {
        if(strcmp(cmd, "createfile") == 0)
        {
            //todo
        }
        else if(strcmp(cmd, "insert") == 0)
        {
            //todo
        }
        else if(strcmp(cmd, "cat") == 0)
        {
            //todo
        }
        else if(strcmp(cmd, "remove") == 0)
        {
            //todo
        }
        else if(strcmp(cmd, "copy") == 0)
        {
            //todo
        }
        else if(strcmp(cmd, "cut") == 0)
        {
            //todo
        }
        else if(strcmp(cmd, "paste") == 0)
        {
            //todo
        }
        else
        {
            invalid_command();
        }
    }
}