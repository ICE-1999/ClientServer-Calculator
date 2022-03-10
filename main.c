/*
        UDP_Client. This Program will implement the Client Side for UDP_Socket Programming.
        It will get some data from user and will send to the server and as a reply from the
        server, it will get its data back.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
   
#define PORT     8080
#define MAXLINE 1024
   
// Driver code
int main() {
int sockfd;
    char buffer[MAXLINE];
    char client_message[100];
    struct sockaddr_in     servaddr;
   
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
   
    memset(&servaddr, 0, sizeof(servaddr));
       
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
     int n, len;
    
    int i=0;
    while(i==0)    
    {
       // for deciding what action you want
        printf("\nEnter Choice: \n");
        printf("Enter N for Adding new number \n");
        printf("Enter D for Delete specific number\n");
        printf("Enter A for Average of all numbers\n");
        printf("Enter m for findng minimum numbers\n");
        printf("Enter M for finding median numbers\n");

        fgets(client_message,sizeof client_message,stdin);

        if(client_message[0]=='N') // for taking number in case of insert
        {
          printf("Enter Number you want to insert \n");
          fgets(client_message,sizeof client_message,stdin);
          int len=0;
          for(int i=0;client_message[i]!='\0';i++)
          {
              len=i;
          }
          client_message[len] = 'N';
          client_message[len+1] = 'A';
        }
        else if(client_message[0]=='D')// for taking number in case of deletion
        {
          printf("Enter Number you want to Delete \n");
          fgets(client_message,sizeof client_message,stdin);
          int len=0;
          for(int i=0;client_message[i]!='\0';i++)
          {
              len=i;
          }
          client_message[len] = 'D';
          client_message[len+1] = 'A';
        }
        else if(client_message[0]=='A') // for finding thr Average
        {
            client_message[0]='S';
            client_message[1] = 'A';
        }
        else if(client_message[0]=='m') // for finding the minimum
        {
            client_message[0]='m';
            client_message[1] = 'A';
        }
        else if(client_message[0]=='M') // for finding the median
        {
            client_message[0]='M';
            client_message[1] = 'A';
        }
        else
        {
          client_message[0]='A';
          i=1;
        }

      sendto(sockfd, client_message, strlen(client_message),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
    printf("Action Performed.\n");
           
    n = recvfrom(sockfd, buffer, MAXLINE, 
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    
    for(int i=0;buffer[i]!='z';i++)
          printf("%c",buffer[i]);
   
    }
        close(sockfd);

        return 0;
}
