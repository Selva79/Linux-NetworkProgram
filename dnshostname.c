/*************************************************************************

 SourceName         :  dnshostname.c                                       
Description           : This program demonstrates the use of DNS and display hostname and IP.                                


 Compile and execute :                                                               
                To Compile The Program  :  #gcc –o dnshostname dnshostname.c
                To Execute The Program   : #./dnshostname

***************************************************************************/ 

/*------------------------------------------ HEADER FILES ------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*-----------------------------------------------------------------------------------------------------------*/


int main()
{
	char hostbuffer[256];
	char *IPbuffer;
	struct hostent *host_entry;
	int hostname;

	hostname = gethostname(hostbuffer, sizeof(hostbuffer));
	if (hostname == -1)
	{
		perror("gethostname");
		exit(1);
	}

	host_entry = gethostbyname(hostbuffer);
	if (host_entry == NULL)
	{
		perror("gethostbyname");
		exit(1);
	}


	IPbuffer = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));   /*	To convert an Internet network address into ASCII string */
	if (IPbuffer==NULL)
	{
		perror("inet_ntoa");
		exit(1);
	}
	printf("Hostname: %s\n", hostbuffer);
	printf("Host IP: %s", IPbuffer);

	return 0;
}

