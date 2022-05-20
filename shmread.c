/*************************************************************************

 SourceName         :  shmread.c                                       

 Description           : Reads from the shared memory and displays the data.                                


 Notes :                                                               
                To Compile The Program  :  #gcc –o shmread shmread.c
                To Execute The Program   : #./shmread

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


int main()                                                   /* Start of main()                                                      */  
{	
	
	int shmid;
  	shmid = shmget(SHMKEY,1024,0);  /* Open the shared memory
                                                                                                   segment                                    */
	if(shmid < 0)       
	{
		printf("\n Shared Memory Segment error. Create shared memory and write first\n");
		exit(0);
	}
  
	char *data = ( char*) shmat(shmid,0,0);      /* Attaching the shared memory to the process    */
                                                                                                 
if(data == (char *) 0)
	{
		printf("\nError In Attaching The Shared Memory : %s\n",
                        strerror(errno));
		exit(0);
	}
          
	  printf("Data from Shared memory         : %s\n",data);

	 if(shmdt(data) < 0)            /* Detach the shared memory                                    */
		printf("\nError In Detaching Shared Memory Segment : %s\n",
                        strerror(errno)); 
 
	if(shmctl(shmid,IPC_RMID,0) < 0)  /* Remove the shared memory segment              */
		printf("\nError In Removing The Shared Memory Segment : %s\n",
                        strerror(errno));
	else
		printf("\nThe Shared Memory Removed Successfully\n");

}

/***************************************************************************/
