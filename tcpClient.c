/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                                                                      
 SourceName         : tcpClient.c                                                                                                   
 Description        : TCP Client for TCP/IP socket 
    compile: gcc –o tcpClient tcpClient.c             
    Run:   ./tcpClient                             
                                                
                                                                      
                                                                      
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define LEN 10000

#define SERV_ADDR   "127.0.0.1" 
#define TCP_PORT           4444
#define TRUE             1
#define FALSE            0   


/*--------------------------------------------------------------------*/


extern int errno;




int debug = FALSE;
int flag = 0;
char msg[LEN];
 
int length = 26;
int s; /* socket */
int clientsocket;
int socks[2];

void socinit(void)
{
        int fd;

        struct sockaddr_in myname;
        printf("Socket Init\n");
        if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
             if (debug)
	       printf("socket error: %s\n", strerror());
             exit(1);
	}

        memset(&myname, 0, sizeof(myname));
        myname.sin_family = AF_INET;
        myname.sin_addr.s_addr = inet_addr(SERV_ADDR);
        myname.sin_port =  TCP_PORT;
	printf("Socket Connect\n");
        fd = connect(s, (struct sockaddr *)&myname, sizeof(myname));
        if (fd == -1) {
                printf("connect():error = %s\n", strerror());
				exit(1);
        }
        printf("Socket Connect success\n");
}

void handler()
{
       int fd;
       
        getchar();

        /* finalize */
        fd = close(s);
        if (debug)
			printf("Client socket close()\n", fd);
  exit(0);
}

int main(int argc, char *argv[], char *env)
{
        int i,len, fd;
        socinit();
        signal(SIGINT,handler); 
        printf("press CTRL C to terminate.\n");
      while(1)
      {
	printf("Enter the Message");
        scanf("%s", msg);  
        printf("Message = %s",msg);
 
/* Client to send message */
        len=strlen(msg);
        printf("Sending Message\n");
        fd = send(s, msg, length, 0);
       

        if (debug) {
                printf("send fd=%d msg=[", fd);
                printf("%s",msg);

                printf("]\n");
        }
        if (fd == -1) {
                printf("send error = %s\n", strerror());
        }
     }
        
}






