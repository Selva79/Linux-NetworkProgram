

/*************************************************************************

 SourceName         :  orphanproex.c                                       
Description           : This program demonstrates the working of a orphanprocess                              


 Compile and execute :                                                               
                To Compile The Program  :  #gcc –o orphanproex orphanproex.c
                To Execute The Program   : #./orphanproex

***************************************************************************/ 
/*--------------------------------------- HEADER FILES ---------------------------------------------*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*-------------------------------------------------------------------------------------------------*/
int main()
{
		
	int pid = fork(); /*Create a child process */

	if (pid > 0)
	{
		printf("\n It is parent process\n"); /* parent process exits before child process*/
		printf("parent process id is %d\n",getpid( ));
		


	}
	else if (pid == 0)
	{
		sleep(10);
		printf("It is child process\n");   /*orphan process is soon adopted by init process, once its parent process dies.*/
		printf("child parent process id is %d\n",getppid( ));
		
	}

	return 0;
}
