#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_INPUT_SIZE 200
#define MAX_CMD_SIZE 50
#define MAX_CMDTYPE_SIZE 10
#define MAX_ADDRESS_SIZE 100

void invalid_command(void);
void commandAndTypefinder(char* input, char* cmd, char* cmdType);
void address_finder(char* input, char* address);

void create_file(char* address);
void cat(char* address);
void insert_str();

int main()
{   
    char *input = (char *)malloc(MAX_INPUT_SIZE * sizeof(char));
    char *cmd = (char *)malloc(MAX_CMD_SIZE * sizeof(char));
    char *cmdType = (char *)malloc(MAX_CMDTYPE_SIZE * sizeof(char));
    char *address = (char *)malloc(MAX_ADDRESS_SIZE * sizeof(char));

    system("clear");
    printf("-------------VIM-------------\n");
    
    while(true)
    {      
        scanf("%[^\n]%*c",input);  
        commandAndTypefinder(input,cmd,cmdType);

        if(strcmp(cmd, "createfile") == 0)
        { 
            if(strcmp(cmdType, "--file") == 0)
            {   
                address_finder(input, address);
                create_file(address);
            }
            else
            {
                invalid_command();
            }
        }
        else if(strcmp(cmd, "insertstr") == 0)
        {
            if(strcmp(cmdType, "--file"))
            {

            }
        }
        else if(strcmp(cmd, "cat") == 0)
        {
            if(strcmp(cmdType, "--file") == 0)
            {
                cat(input);
            }
            else
            {
                invalid_command();    
            }
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
            system("clear");
            break;
        }
        else
        {
            invalid_command();
        }
    }
}

void invalid_command(void)
{
    printf("invalid command!\n");
}

void commandAndTypefinder(char* input, char* cmd, char* cmdType)
{
    int i = 0;
    while(true)
    {   
        if(input[i] == ' ' || input[i] == '\0' || input[i] == '\n')
        {   
            cmd[i] = '\0';
            i++;
            break;
        }
        cmd[i] = input[i];
        i++;
    }
    int j = 0;
    while(true)
    {   
        if(input[i] == ' ' || input[i] == '\0' || input[i] == '\n')
        {   
            cmdType[j] = '\0';
            break;
        }
        cmdType[j] = input[i];
        i++;
        j++;
    }
}

void address_finder(char* input, char* address)
{   
    int i = 0;
    int j = 0;

    while(input[i] != '\n' && input[i] != '\0')
    {   
        if(input[i] == '/')
        {
            while(input[i] != '"' && input[i] != '\n' && input[i] != '\0')
            {
                address[j] = input[i];
                i++;
                j++;
            }

            address[j] = '\0';
        }
        i++;
    }
}

void create_file(char* address)
{   
    const char s[2] = "/";
    char *token;
    
    /* get the first token */
    token = strtok(address, s);

    int check;
    int HowManyCdNeeds = 0;

    if(strcmp(token,"root") == 0 && address[0] == '/')
    {
        /* walk through other tokens */
        while( token != NULL )
        {   
            char* tmp = token;
            token = strtok(NULL, s);

            if(token != NULL)
            {
                check = mkdir(token,0777);
                chdir(token);
                HowManyCdNeeds++;
            }
            else if(token == NULL)
            {   
                chdir("..");
                HowManyCdNeeds--;
                rmdir(tmp);
                FILE *file;
                file = fopen(tmp, "r");
                if(file != 0)
                {
                    puts("This file alredy exists\n");
                }
                else
                {
                    FILE *myfile = fopen(tmp, "w");
                    fclose(myfile);
                }
            }
        }
        for(int i = 0; i < HowManyCdNeeds; i++)
        {
            chdir("..");
        }
    }
    else
    {
        invalid_command();    
    }
       
}

void get_all_char(char* string, FILE *fp)
{
    char charachter;
    while((charachter = getc(fp)) != EOF)
    {
        string[strlen(string)] = charachter;
    }
}

void cat(char* input)
{   
    //Finding filename
    int i = 11, j = 0;
    char filename[50];

    while(input[i] != '\0' && input[i] != '\n')
    {   
        filename[j] = input[i];
        j++;
        i++;
    }

    //Check if it exists or not

    FILE *file;

    if ((file = fopen(filename, "r")))
    {
        char c;
        while((c = getc(file)) != EOF)
        {
            printf("%c",c);
        }
        printf("\n");
        fclose(file);
    }
    else
    {
        printf("it Doesn't Exist! \n");
    }
}

void insert_str();