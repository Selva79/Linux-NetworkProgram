/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                                                                      
  SourceName         : tcpServer.c                                     
  Description        : TCP Server program for TCP/IP socket   
    compile: gcc –o tcpServer tcpServer.c             
    Run:   ./tcpServer          
*                                                                      
*----------------------------------------------------------------------*/


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


  
#define TRUE             1
#define FALSE            0   
/*--------------------------------------------------------------------*/
extern int errno;

#define soclose     close
#define sockerror() strerror(errno)




/* define constants */
#define NONE 0
#define LEN 10000

/* define global variables */

int flag = NONE;
int debug = FALSE;
char msg[LEN];
int length = 0;
char temp[LEN];
int s;  /* socket */
int clientsocket;
int socks[2];
struct timeval timeout = {30, 0 };


void process_recv(void)
{
        int c, rc,fd, len = 0;

         printf("press CTRL C to terminate.\n");
      while(1)
      {
        printf("Waiting for packet\n");
        do {
                { 
                  fd_set fd_s;
                  FD_ZERO(&fd_s); 
                  FD_SET(socks[0], &fd_s);
                      
                  rc = select(FD_SETSIZE, &fd_s, NULL, NULL, &timeout);
                } 
                if (rc == -1) {
                        printf("select error = %s\n",sockerror());

                }if (rc > 0) {
                        printf("Packet Received\n");
                        len = recv(clientsocket, temp, LEN, 0);
			temp[len] = 0;                        
                        printf("***%s***\n",temp);
                     
		}else
                {                      
                      printf("Time out, Terminate(y/n)?");
                      c = getchar();
                      if (c == 'y')
                           rc = -1;
                }
               
        } while (rc == 0);
        printf("packet arrived\n");

        if (len == -1) {
                printf("error = %s\n",sockerror());
                sleep(100);
        }
  }
}


void socinit(void)
{
        int rc;

        struct sockaddr_in myname;
        struct sockaddr clientaddress;
        int addrlen;

        if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			printf("Socket error %s\n",sockerror());
                        exit(1);
        }
        if (debug)
		printf("socket socket=%d\n", s);

/* bind */

        memset(&myname, 0, sizeof(myname));
        myname.sin_family = AF_INET;
        myname.sin_addr.s_addr = INADDR_ANY;
        myname.sin_port =  4444;

        rc = bind(s, (struct sockaddr *)&myname, sizeof(myname));
       

        if (debug) printf("bind rc=%d\n", rc);
        if (rc == -1) {
                printf("bind error = %s\n",sockerror());
        }

/* listen */

        rc = listen(s, 2);
        if (debug)
			printf("listen rc=%d\n", rc);
        printf("waiting connection\n");

/* accept */

        addrlen = sizeof(clientaddress);
       
        
        clientsocket = accept(s, &clientaddress, &addrlen);
        printf("clientsocket=%d\n",clientsocket);
        if (debug)
			printf("accept\n");
       
        socks[0] = clientsocket;
}
void handler()
{
    short int rc;
    printf("Closing socket..\n");
   rc = soclose(clientsocket);
        if (debug)
			printf("client socket soclose()\n", rc);
        rc = soclose(s);
        if (debug)
			printf("server socket soclose()\n", rc);
  exit(0);
}
int main(int argc, char *argv[], char *env)
{
        int i;
	 short int rc;
        socinit();

/* main loop */

        
        signal(SIGINT,handler);                      //set the handler for SIGINT  
        printf("start receive\n");  
        process_recv();
        



       

        return 0;
}


