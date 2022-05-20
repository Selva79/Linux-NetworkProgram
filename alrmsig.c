
/*************************************************************************

 SourceName         :  alrmsig.c                                       
Description           : This program demonstrates the working of a SIGALRM.                                


 Compile and execute :                                                               
                To Compile The Program  :  #gcc –o alrmsig alrmsig.c
                To Execute The Program   : #./alrmsig

***************************************************************************/ 

/*------------------------------------------ HEADER FILES ------------------------------------------*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/unistd.h>   


/*-----------------------------------------------------------------------------------------------------------*/

void  handler()                                              /* Signal handler function                    */ 
{
              printf("\n SIGNAL ALARM Triggered !\n");
}

int main()                                                        /* main()                                */
{
	signal(SIGALRM,handler);                                   /* set the signal                                          */
	alarm(10);                                                  /* set alrarm to trigger with specified duration           */
 
	printf("\n Set alarm . wait fpr Signal handler to handle the SIGALRM...\n");
	pause();
	return 0;
}


