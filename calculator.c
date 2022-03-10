
// Server side implementation of UDP client-server model
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
   
void swap(int *p,int *q)
{
   int t;
   
   t=*p; 
   *p=*q; 
   *q=t;
}

void sort(int a[],int n) // for sorting numbers for median
{ 
   int i,j,temp;

   for(i = 0;i < n-1;i++) {
      for(j = 0;j < n-i-1;j++) {
         if(a[j] > a[j+1])
            swap(&a[j],&a[j+1]);
      }
   }
}


// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char hello[100];
    int store[1000];
    int counter=0;
    struct sockaddr_in servaddr, cliaddr;
       
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
       
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
       
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
       
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
 
    int len, n;
    len = sizeof(cliaddr);  //len is value/resuslt

   int i=0;
   while(i==0)
   {
   
    n = recvfrom(sockfd, buffer, MAXLINE, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);    
    int num=0;
    int temp=0;
    for(int i=0;buffer[i]!='A';i++) // for decoding number
    {
          if(buffer[i+1]!='A')
          {
             num = num*10+((buffer[i])-48);
          }
          else
          {
            temp=i;
          }
       //   printf("%c ",buffer[i]);
    }

    if(buffer[temp]=='N') // for inserion
    {
       store[counter]=num;
       counter++;
       hello[0] = 'I';
       hello[1] = 'z';
       printf("Number is inserted  %d\n",num); 

    }
    else if(buffer[temp]=='D') // for deletion
    {
       int temp_array[counter];
       for(int i=0;i<counter;i++)
       {
         if(num==store[i])
         {
           temp_array[i]=0;
         }
         else
         {
           temp_array[i]=store[i];
         }
       }
       int counter1=counter;
       int temp_counter = 0;
       for(int i=0;i<counter1;i++)
       {
         if(temp_array[i]!=0)
         {
            store[temp_counter]=temp_array[i];
            temp_counter++;
         }
         else
         {
             counter--;
         }
       }
       hello[0] = 'D';
       hello[1] = 'z';
      printf("Number is Deleted if found  %d\n",num); 

    }
    else if(buffer[temp]=='S') // for sum
    {
      int sum=0;
      for(int i=0;i<counter;i++)
         sum = sum + store[i];

      int average = sum/counter;
	    sprintf(hello, "%d", average);
      int counter22=0;
       while(average>0)
       {
        average=average/10;
        counter22++;
       }
     hello[counter22]='z';
      printf("Average Send back  \n"); 
      //printf("SUM IS  %d\n",sum);   
    }
    else if(buffer[temp]=='m') // for minimum
    {
      int min1=10000;
      for(int i=0;i<counter;i++)
      {
        if(min1>store[i])
            min1=store[i];
      }
     sprintf(hello, "%d", min1);
     int counter22=0;
     while(min1>0)
     {
       min1=min1/10;
       counter22++;
     }
     hello[counter22]='z';
     // printf("minimum IS  %d\n",min1);
      printf("Median Send back  \n"); 
   
    }
    else if(buffer[temp]=='M') // for median
    {
          // First we sort the array
       sort(store,counter);
       int median = store[(counter+1) / 2 - 1]; 
       sprintf(hello, "%d", median);
       int counter22=0;
       while(median>0)
       {
        median=median/10;
        counter22++;
       }
     hello[counter22]='z';
      printf("Minimum Send back  \n"); 
   //    printf("minimum IS  %d\n",median); 
    }
    else
    {
      hello[0]='z';
       i=1;
    }

    printf("\n");

    sendto(sockfd,hello, strlen(hello), 
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
   }   
    return 0;
}