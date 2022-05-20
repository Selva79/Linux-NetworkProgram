/*************************************************************************

 SourceName         :  shmwrite.c                                       

 Description           : shared memory segment creation and write the data into it. To read the data , shared memory reader to connect with segment and read.                                


 Notes :                                                               
                To Compile The Program  :  #gcc –o shmwrite shmwrite.c
                To Execute The Program   : #./shmwrite

***************************************************************************/ 
 

/*-------------------------------------- HEADER FILES -------------------------------------------------*/

       
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

/*-------------------------------------------------------------------------------------------------------------*/

#define SHMKEY          0x123
#define PERMS           0666
int main()                                                   /* Starting Of main()                                                */
{
                                     
	int shmid;
        char msg[1024];
	shmid = shmget(SHMKEY,1024,IPC_CREAT|PERMS); /* Shared memory segment  */
                                                                                                  
	if(shmid < 0)                                             
	{
		printf("\n Shared memory creation error,%s",strerror(errno));
		exit(0);
	}
  
	char *data = (char *)shmat(shmid,0,0);                              /* Attach segment to the process       */
                                                                                             
	if(data == (char *) 0)  
	{
		printf("\n Shared memory attachment error, %s", strerror(errno));
		exit(0);
	}
                                         
            /* Get the data from the user in the format specified in the CFG_SHM structure.        */

	printf("\nEnter The user data ");      
	scanf("%[^\n]%*c", msg);
	printf("\n user data entered %s",msg);
	memcpy((void *)data,(const void *)&msg,sizeof(msg));  
                                                               
      	if(shmdt(data) < 0)      /* Detach the shared memory                                           */
		printf("\nError In Detaching The Shared Memory segment, %s\n", error(errno));
}
/***************************************************************************/
