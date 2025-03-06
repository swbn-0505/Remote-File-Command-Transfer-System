#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct sockaddr_in serv_addr , cli_addr;
int sockfd , bindfd , listenfd , acceptfd , cli_addr_len , r , w;

unsigned short serv_port = 25020;
char serv_ip[] = "127.0.0.1"; //THIS IS THE CLIENT IP USED FOR TESTING PURPOSE . CHANGE DURING USE . 

char rbuff[2048];
char sbuff[2048];

int main()
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serv_port);
    inet_aton(serv_ip , (&serv_addr.sin_addr));
    
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if(sockfd < 0)
    {
        printf("\nSERVER ERROR : Cannot create socket.\n");
        exit(1);
    }
    
    bindfd = bind(sockfd , (struct sockaddr*)&serv_addr , sizeof(serv_addr));
    if(bindfd < 0)
    {
        printf("\nSERVER ERROR : Cannot Bind.\n");
        close(sockfd);
        exit(1);
    } 
    
    listenfd = listen(sockfd , 5);
    if(listenfd < 0)
    {
        printf("\nSERVER ERROR : Cannot listen.\n");
        close(sockfd);
        exit(1);
    }
    
    cli_addr_len = sizeof(cli_addr);
    
    printf("\nListening to client....press Cntrl C to stop...\n"); 
    acceptfd = accept(sockfd , (struct sockaddr*)&cli_addr , &cli_addr_len);
        
    if(acceptfd < 0)
    {
        printf("\nSERVER ERROR : Cannot accept.\n");
        close(sockfd);
        exit(1);
    }
        
        printf("\nConnection with %s accepted.\n" , inet_ntoa(cli_addr.sin_addr));
        
    for(;;)
    {
        r = read(acceptfd , rbuff , 2048);
        if(r < 0)
        {
            printf("\nSERVER ERROR : Cannot read 1.\n");
            close(sockfd);
            exit(1);
        }
        else
        {
            rbuff[r] = '\0';
            //char cmd[128] = "";
            //char filename[128] = ">abc";
            strcat(rbuff , ">abc");
            system(rbuff);
            
            char sbuff1[2048] = "";
            
            FILE * fp = fopen("abc" , "r");
            
            while(fgets(sbuff , 2048 , fp) != NULL)
            {
                strcat(sbuff1 , sbuff);
            }
            
            fclose(fp);
            
            w = write(acceptfd , sbuff1 , 2048);
            if(w < 0)
            {
                printf("\nSERVER ERROR : Cannot write 1.\n");
                close(sockfd);
                exit(1);
            }
            
            r = read(acceptfd , rbuff , 2048);
            if(r < 0)
            {
                printf("\nSERVER ERROR : Cannot read 2.\n");
                close(sockfd);
                exit(1);
            }
            else
            {
                rbuff[r] = '\0';
                
                char filename2[128] = ">def";
                char find[128] = "find ";
                strcat(rbuff , "*");
                strcat(find , rbuff);
                strcat(find , filename2);
                printf("\n%s\n" , find);
                system(find);
                
                char sbuff2[2048] = "";
                char sbuff3[2048] = "";
            
                FILE * fp = fopen("def" , "r");
            
                while(fgets(sbuff2 , 2048 , fp) != NULL)
                {
                    strcat(sbuff3 , sbuff2);
                }
            
                fclose(fp);
                
                w = write(acceptfd , sbuff3 , 2048);
                if(w < 0)
                {
                    printf("\nSERVER ERROR : Cannot write 2.\n");
                    close(sockfd);
                    exit(1);
                }
                
                r = read(acceptfd , rbuff , 2048);
                if(r < 0)
                {
                    printf("\nSERVER ERROR : Cannot read 2.\n");
                    close(sockfd);
                    exit(1);
                }
                else
                {
                    rbuff[r] = '\0';
                    char ll[128] = "ls -l ";
                    
                    strcat(ll , rbuff);
                    strcat(ll , ">pqr");
                    
                    puts(ll);
                    
                    system(ll);
                    
                    char sbuff4[2048] = "";
                    char sbuff5[2048] = "";
                    char sbuff6[2048] = "";
            
                    FILE * fp = fopen("pqr" , "r");
            
                    while(fgets(sbuff4 , 2048 , fp) != NULL)
                    {
                        strcat(sbuff5 , sbuff4);
                    }
            
                    fclose(fp);
                    if(sbuff5[0] == 't')
                    {
                        strcat(sbuff6 , "This is Folder...cannot download");
                    }
                    else if(sbuff5[3] == 'x')
                    {
                        strcat(sbuff6 , "This is Executable file...cannot download");
                    }
                    else
                    {
                        char concat[128] = "cat ";
                        strcat(concat , rbuff);
                        strcat(concat , ">download");
                        system(concat);
                        
                        char sbuff7[2048] = "";
                        
                        FILE * fp = fopen("download" , "r");
            
                        while(fgets(sbuff7 , 2048 , fp) != NULL)
                        {
                            strcat(sbuff6 , sbuff7);
                        }
            
                        fclose(fp);
                    }
                    w = write(acceptfd , sbuff6 , 2048);
                    if(w < 0)
                    {
                        printf("\nSERVER ERROR : Cannot write 3.\n");
                        close(sockfd);
                        exit(1);
                    }
                }
                
            }
        }
    }
    
    return 0;
}
