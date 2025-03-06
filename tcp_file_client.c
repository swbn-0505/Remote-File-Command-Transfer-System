#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct sockaddr_in serv_addr;
int sockfd , connfd , r , w;

unsigned short serv_port = 25020;
char serv_ip[] = "127.0.0.1"; //THIS SERVER IP IS USED FOR TESTING PURPOSE . CHANGE DURING USE.

char rbuff[2048];
char sbuff[2048];
char sbuff1[2048];
char sbuff2[2048];

int main()
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serv_port);
    inet_aton(serv_ip , (&serv_addr.sin_addr));
    
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if(sockfd < 0)
    {
        printf("\nCLIENT ERROR : Cannot create socket.\n");
        exit(1);
    }
    
    connfd = connect(sockfd , (struct sockaddr*)&serv_addr , sizeof(serv_addr));
    if(connfd < 0)
    {
        printf("\nCLIENT ERROR : Cannot Connect.\n");
        close(sockfd);
        exit(1);
    } 
    
    printf("\nConnected to server.\n");
    
    for(;;)
    {
        printf("\nEnter Command : \n");
        gets(sbuff);
        
        w = write(sockfd , sbuff , 2048);
        if(w < 0)
        {
            printf("\nCLIENT ERROR : Cannot write 1.\n");
            close(sockfd);
            exit(1);
        }
        
        r = read(sockfd , rbuff , 2048);
        if(r < 0)
        {
            printf("\nCLIENT ERROR : Cannot read 1.\n");
            close(sockfd);
            exit(1);
        }
        else
        {
            rbuff[r] = '\0';
            
            printf("\nSERVER :\n%s\n" , rbuff);
            
            printf("\nEnter Filename : \n");
            gets(sbuff1);
            
            w = write(sockfd , sbuff1 , 2048);
            if(w < 0)
            {
                printf("\nCLIENT ERROR : Cannot write 2.\n");
                close(sockfd);
                exit(1);
            }
            r = read(sockfd , rbuff , 2048);
            if(r < 0)
            {
                printf("\nCLIENT ERROR : Cannot read 1.\n");
                close(sockfd);
                exit(1);
            }
            else
            {
                rbuff[r] = '\0';
            
                printf("\nSERVER :\n%s\n" , rbuff);
                
                printf("\nSpecify Filename : \n");
                gets(sbuff2);
                w = write(sockfd , sbuff2 , 2048);
                if(w < 0)
                {
                    printf("\nCLIENT ERROR : Cannot write 2.\n");
                    close(sockfd);
                    exit(1);
                }
                r = read(sockfd , rbuff , 2048);
                if(r < 0)
                {
                    printf("\nCLIENT ERROR : Cannot read 1.\n");
                    close(sockfd);
                    exit(1);
                }
                else
                {
                    rbuff[r] = '\0';
                    
                    if(strcmp(rbuff , "This is Folder...cannot download") == 0 || strcmp(rbuff , "This is Executable file...cannot download") == 0)
                    {
                        printf("\nSERVER : %s.\n" , rbuff);
                    }
        
                    else
                    {
                        char temp[2048] = "";
                        char cmp_arr[2048] = "";
                        FILE * fp = fopen(sbuff2 , "r");
                        if(fp == NULL)
                        {
                            FILE * fp1 = fopen(sbuff2 , "w");                 
                            fputs(rbuff , fp1);
                            printf("\nCLIENT : File downloaded successfully.\n");   
                            fclose(fp1);
                        }
                        else
                        {
                            while(fgets(temp , 2048 , fp) != NULL)
                            {
                                strcat(cmp_arr , temp);
                            }
                            
                            if(strcmp(cmp_arr , rbuff) == 0)
                            {
                                printf("\nFile already present.\n");
                            }
                            else
                            {
                                FILE * fp2 = fopen(sbuff2 , "w");                 
                                fputs(rbuff , fp2);
                                printf("\nCLIENT : File downloaded successfully.\n");   
                                fclose(fp2);
                            }
                        }
                        //fclose(fp);
                    }
                }
            }
            char exit_cmd[10];
            printf("\nDo you want to continue ?[Y/n] : ");
            gets(exit_cmd);
            if(strcmp(exit_cmd , "n") == 0)
            {
                close(sockfd);
                exit(1);
            }
        }
    }
    
    return 0;
}
