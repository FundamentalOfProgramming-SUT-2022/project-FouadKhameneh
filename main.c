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

void command_check(char* input, char* cmd);  //splits Command from entire input
void create_file(char* input);

int main()
{
    char *cmd = (char *)malloc(25 * sizeof(char));
    char *input = (char *)malloc(100 * sizeof(char));

    while(true)
    {      
        scanf("%[^\n]%*c",input);
        command_check(input,cmd);

        if(strcmp(cmd, "createfile") == 0)
        {
            create_file(input);
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
        else if(strcmp(cmd, "exit") == 0)
        {
            break;
        }
        else
        {
            invalid_command();
        }

        scanf("%[^\n]%*c",input);
        command_check(input,cmd);
    }
}

void command_check(char* input, char* cmd)
{   
    int i = 0;

    while(input[i] != ' ')
    {
        cmd[i] = input[i];
        i++;
    }
}

void create_file(char* input)
{
    //todo
}