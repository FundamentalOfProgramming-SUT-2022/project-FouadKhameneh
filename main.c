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

char clipboard[1000] = {'\0'};

void invalid_command(void);
void commandAndTypefinder(char* input, char* cmd, char* cmdType);
void address_finder(char* input, char* address);
void goToAddress(char* address);                                 
void goToProjectFile(void);

void create_file(char* address);
void cat(char* address);
void insert_str(char* input);
void remove_str(char* input);
void tree(char *basePath, const int root);

int main()
{   
    mkdir("root",S_IRWXU);

    system("clear");
    printf("-----------------------------\n");
    printf("-------------VIM-------------\n");
    printf("-----------------------------\n\n");
    
    char *input = (char *)malloc(MAX_INPUT_SIZE * sizeof(char));
    char *cmd = (char *)malloc(MAX_CMD_SIZE * sizeof(char));
    char *cmdType = (char *)malloc(MAX_CMDTYPE_SIZE * sizeof(char));
    char *address = (char *)malloc(MAX_ADDRESS_SIZE * sizeof(char));
    char *crash_handler = "c";

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
            if(strcmp(cmdType, "--file") == 0)
            {
                insert_str(input);
            }
            else
            {
                invalid_command();
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
        else if(strcmp(cmd, "removestr") == 0)
        {
            if(strcmp(cmdType, "--file") == 0)
            {
                remove_str(input);
            }
            else
            {
                invalid_command();    
            }
        }
        else if(strcmp(cmd, "copystr") == 0)
        {
            printf("\nits not Completed :(\n");
        }
        else if(strcmp(cmd, "cutstr") == 0)
        {
            printf("\nits not Completed :(\n");
        }
        else if(strcmp(cmd, "pastestr") == 0)
        {
            printf("\nits not Completed :(\n");
        }
        else if(strcmp(cmd, "tree") == 0)
        {   
            printf("\nStarting From './root/dir1' like the instruction said\n");
            tree("./root/dir1",1);
        }
        
        else if(strcmp(cmd, "exit") == 0)
        {   
            system("clear");
            break;
        }
        else if(strcmp(input," ") == 0)
        {
            printf("dude wtf\n");
            return 1;
        }
        else
        {
            invalid_command();
        }

    }
}

void invalid_command(void)
{
    printf("\ninvalid!\n");
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

void goToAddress(char* address)  //Goes to Address
{   
    char* token;
    char* FileName;
    token = strtok(address, "/");
    while(token != NULL) 
    {   
        FileName = token;
        chdir(token);
        token = strtok(NULL, "/");
    }
}

void goToProjectFile()
{   
    char cwd[MAX_ADDRESS_SIZE];
    getcwd(cwd, 100);
    int cwdsize = strlen(cwd);
    while(cwd[cwdsize - 1] != 't' || cwd[cwdsize- 2 ] != 'o' || cwd[cwdsize - 3] != 'o' || cwd[cwdsize - 4] != 'r' || cwd[cwdsize - 5] != '/')
    {
        chdir("..");
        getcwd(cwd, 100);
        cwdsize = strlen(cwd);
    }
    chdir("..");
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
            check = mkdir(token,0777);
            chdir(token);
            HowManyCdNeeds++;
            
            char* tmp = token;
            token = strtok(NULL, s);

            if(token == NULL)
            {   
                chdir("..");
                HowManyCdNeeds--;
                rmdir(tmp);
                FILE *file;
                file = fopen(tmp, "r");
                if(file != 0)
                {
                    printf("\nThis file alredy exists\n");
                }
                else
                {
                    FILE *myfile = fopen(tmp, "w");
                    fclose(myfile);
                }
                fclose(file);
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

void cat(char* input)
{   
    //Finding address
    int i = 11, j = 0;
    char address[50];
    char addressTmp[50];

    char s[2] = "/";

    while(input[i] != '\0' && input[i] != '\n')
    {   
        address[j] = input[i];
        addressTmp[j] = input[i];
        j++;
        i++;
    }
    address[j] = '\0';
    addressTmp[j] = '\0';

    char* addressPointer = address;
    addressPointer = strtok(addressPointer,s);
    char* addressPointerOneBack;

    while(addressPointer != NULL) 
    {   
        addressPointerOneBack = addressPointer;
        addressPointer = strtok(NULL, "/");
    }

    goToAddress(addressTmp);

    FILE *file;

    if ((file = fopen(addressPointerOneBack, "r")))
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
        printf("\nit Doesn't Exist! \n");
    }

    goToProjectFile();
}

void insert_str(char* input)
{   
    char s[2] = " ";
    char s1[2] = "/";

    for(int i = 0; input[i] != '\0' && input[i] != '\n'; i++)
    {   
        if(input[i] == '"')
        {   
            printf("\nWe Dont use \" here! \n");
            return;
        }
    }

    //Seprating by space and using pointer array to ...
    char* inputTmp[10];
    char* token;
    token = strtok(input,s);
    int i = 0;
    while( token != NULL )
    {   
        inputTmp[i] = token;
        token = strtok(NULL, s);
        i++;
    }

    char address[50];
    strcpy(address,inputTmp[2]);
    char FileName[50];

    i = strlen(address) - 1;
    int j = 0;

    //This gets Filename
    while(true)
    {
        if(address[i] == '/')
        {
            FileName[j] = '\0';
            break;
        }
        FileName[j] = address[i];
        i--;
        j++;
    }

    i = 0;
    j = strlen(FileName);

    while(i < j)
    {
        char tmp = FileName[i];
        FileName[i] = FileName[j-1];
        FileName[j-1] = tmp;
        i++;
        j--;
    }

    //position handling
    int line = 0;
    int point = 0;
    int tmpint = 0;
    int is2NogteTrue = 0;

    while(true)
    {
        if(inputTmp[6][tmpint] == '\0' || inputTmp[6][tmpint] == '\n')
        {
            break;
        }
        else if(inputTmp[6][tmpint] == ':')
        {
            is2NogteTrue = 1;
        }
        else if(is2NogteTrue == 0)
        {
            line *= 10;
            line += (inputTmp[6][tmpint] - '0');
        }
        else if(is2NogteTrue == 1)
        {
            point *= 10;
            point += (inputTmp[6][tmpint] - '0');
        }

        tmpint++;
    }

    //insertstr --file /root/dir1/text.txt --str AAA --pos 3:5  
    //inputTmp is Array pointer that gives part of input
    //address is path

    if(strcmp(inputTmp[3],"--str") == 0 && strcmp(inputTmp[5],"--pos") == 0)
    {   
        goToAddress(inputTmp[2]);

        FILE *file;
        file = fopen(FileName,"r");
        if(file == 0)
        {
            printf("\nThis file doesn't exist! \n");
            fclose(file);
            return;
        }
        i = 1, j = 0;
        char c;
        char BeforeString[10000] = {};
        int x = 0;
        while (i != line || j != point)
        {
            c = fgetc(file);
            if(c == EOF)
            {
                printf("\ninvalid Position!\n");
                fclose(file);
                return;
            }
            j++;
            BeforeString[x] = c;
            BeforeString[x + 1] = '\0';
            x++;
            if(c == '\n')
            {
                i++;
                j = 0;
            }
        }
        x = 0;
        char AfterString[10000];
        while(true)
        {
            c = fgetc(file);
            if(c == EOF)
            {
                break;
            }
            AfterString[x] = c;
            AfterString[x + 1] = '\0';
            x++;
        }
        fclose(file);

        //Uses W format And Implents
        file = fopen(FileName,"w");
        fprintf(file,"%s%s%s",BeforeString,inputTmp[4],AfterString);
        fclose(file);

        goToProjectFile();
        printf("\nSuccessfully inserted the String! \n");
        return;
    }
    else
    {
        invalid_command();
        return;
    }
}

void remove_str(char* input)
{
    char s[2] = " ";
    char s1[2] = "/";

    for(int i = 0; input[i] != '\0' && input[i] != '\n'; i++)
    {   
        if(input[i] == '"')
        {   
            printf("We Dont use \" here! \n");
            return;
        }
    }

    //Seprating by space and using pointer array to ...
    char* inputTmp[10];
    char* token;
    token = strtok(input,s);
    int i = 0;
    while( token != NULL )
    {   
        inputTmp[i] = token;
        token = strtok(NULL, s);
        i++;
    }

    char address[50];
    strcpy(address,inputTmp[2]);
    char FileName[50];

    i = strlen(address) - 1;
    int j = 0;

    //This gets Filename
    while(true)
    {
        if(address[i] == '/')
        {
            FileName[j] = '\0';
            break;
        }
        FileName[j] = address[i];
        i--;
        j++;
    }

    i = 0;
    j = strlen(FileName);

    while(i < j)
    {
        char tmp = FileName[i];
        FileName[i] = FileName[j-1];
        FileName[j-1] = tmp;
        i++;
        j--;
    }

    //position handling
    int line = 0;
    int point = 0;
    int tmpint = 0;
    int is2NogteTrue = 0;

    while(true)
    {
        if(inputTmp[4][tmpint] == '\0' || inputTmp[4][tmpint] == '\n')
        {
            break;
        }
        else if(inputTmp[4][tmpint] == ':')
        {
            is2NogteTrue = 1;
        }
        else if(is2NogteTrue == 0)
        {
            line *= 10;
            line += (inputTmp[4][tmpint] - '0');
        }
        else if(is2NogteTrue == 1)
        {
            point *= 10;
            point += (inputTmp[4][tmpint] - '0');
        }

        tmpint++;
    }

    //insertstr --file /root/dir1/text.txt --str AAA --pos 3:5  
    //removestr --file /root/dir1/text.txt --pos 2:1 --size 3 --b

    if(strcmp(inputTmp[3],"--pos") == 0 && strcmp(inputTmp[5],"--size") == 0)
    {
        goToAddress(inputTmp[2]);

        FILE *file;
        file = fopen(FileName,"r");
        if(file == 0)
        {
            printf("\nThis file doesn't exist! \n");
            fclose(file);
            return;
        }

        //
        if(strcmp(inputTmp[7],"--f") == 0)
        {

        }
        else if(strcmp(inputTmp[7],"--b") == 0)
        {

        }
        else
        {
            printf("\nInvalid Type of F/B\n");
        }
        //

        goToProjectFile();

    }
    else
    {
        invalid_command();
        return;
    }

}

void tree(char *basePath, const int root)
{
    int i;
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
    {
        printf("\nDir1 Doesn't exist! \n");
        return;
    }
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            for (i = 0; i < root; i++) 
            {
                if (i % 2 == 0 || i == 0)
                {
                    printf("%c", '|');
                }
                else
                {
                    printf(" ");
                }

            }

            printf("%c%c%s\n", '|', '-', dp->d_name);

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            tree(path, root + 2);
        }
    }

    closedir(dir);
}