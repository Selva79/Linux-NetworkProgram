
/*----------------------------------------------------------------------
                                                                      
 SourceName         : rawsockex.c                                       
                                                                      
 Description        : Program demonstrating the use of RawSockets to ping   
                                                                      
                                                           
   compile: gcc –o rawsockex rawsockex.c             
   Run:  sudo ./rawsockex                             
                                                                      
----------------------------------------------------------------------*/

/*--------------------------------Header Files-------------------------*/



#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
/*--------------------------------------------------------------------*/


#define MAXPACKET        1024      
#define SERV_HOST_ADDR   "127.0.0.1" 



u_char sendpack[MAXPACKET];
u_char recvpack[MAXPACKET];
struct sockaddr_in dest;

int sockfd;
extern int errno;

int send_ping()
{
  register struct icmp *icp;
  int n;
  static int seqno = 1;
  icp = (struct icmp *) sendpack;
  icp->icmp_type = ICMP_ECHO;                 //fill the ICMP header 
  icp->icmp_code = 0;                          
  icp->icmp_cksum = 0;
  icp->icmp_id = getpid();
  icp->icmp_seq = seqno;
  n = sendto(sockfd,sendpack,sizeof(sendpack),0,(struct sockaddr *) &dest,
             sizeof(dest));
  if(n < 0)
    printf("Send Error:%s\n",strerror(errno));
  else
    printf("Ping Message sent: icmp_seq = %d\n",seqno); 
  seqno++;                                     //after sending increment 
  return 0;                                    //sequence number         
}

int recv_ping()
{
  register struct icmp *icp;
  struct ip *ip;
  int n,iphdrlen,clilen;
  struct sockaddr_in from;
  clilen = sizeof(from);
  while(1)
    {
	printf("in recv ping\n");
     n = recvfrom(sockfd,recvpack,sizeof(recvpack),0,(struct sockaddr *)&from,
                 (int *)&clilen);
     if(n < 0)
     {
       if(errno == EINTR)                  //continue if interrupted by signal
	 continue;                        
      else
       printf("Receive Error:%s\n",strerror(errno));
     }   
     else 
     {
	     printf("received ping msg\n");
       ip = (struct ip *) recvpack;        //get the ip header length
       iphdrlen = ip->ip_hl << 2;          //convert # 16-bit words to #bytes
       
       icp = (struct icmp *)(recvpack + iphdrlen); //get the ICMP header
       printf("ping reply %d\n",icp->icmp_seq);
       printf("reply type %d\n",icp->icmp_type);
       
     }
   break;   
  }  
return 0;
}

void handler()
{
  printf("Closing socket..\n");
  close(sockfd);                      //close the raw socket
  exit(0);
}



int main()
{
  struct protoent *proto;
  bzero((char *)&dest,sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
  
  if((proto = getprotobyname("icmp")) == NULL)   /* Check icmp */
    printf("Unknown protocol\n");                
  
  if((sockfd = socket(AF_INET,SOCK_RAW,proto->p_proto)) < 0)   //open a rawsocket
    printf("Can't create raw socket\n");                       
  
  signal(SIGINT,handler);                      //set the handler for SIGINT    
  while(1)                                   
    {
      send_ping();                             //send ping
      recv_ping();                             //receive ping
      sleep(2);                                       
    }
  return 0;
}


