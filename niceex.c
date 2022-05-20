
/*************************************************************************

 SourceName         :  niceex.c                                       
Description           : This program demonstrates the working of a nice() system call                             


 Compile and execute :                                                               
                To Compile The Program  :  #gcc –o niceex niceex.c
                To Execute The Program   : #./niceex

***************************************************************************/ 


/*---------------------------------------- HEADER FILES ---------------------------------------------*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>

/*-----------------------------------------------------------------------------------------------------------*/

int main()                                                       /* Start of main()                                                    */
{
	int i,pid,retnice;
	printf("\nPress CTRL C To Stop Process\n\n");
	printf("\n Check the printing pattern for nice() system call functionality\n");
	pid=fork();
	for(;;)
	{
		printf("\n");
		if(pid==0)
		{
			retnice=nice(-10);   /* Setting a higher priority for the child. A lower nice value means a higher priority.                 */ 
			printf("The Child Gets Higher CPU Priority\n");
			sleep(1);
		}
		else
		{
			retnice=nice(10);    /* Setting a lower priority for the parent.A higher nice value means a low priority.                  */   
			printf("The Parent Gets Lower CPU Priority\n");
			sleep(1);
		}
		
		sleep(4);
		
	}
	return 0;
}

