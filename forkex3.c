/*************************************************************************

 SourceName         :  forkex3.c                                       
Description           : This program demonstrates the working of a fork() system call. Parent to create child and identify parent, child process using PID                              


 Compile and execute :                                                               
                To Compile The Program  :  #gcc –o forkex3 forkex3.c
                To Execute The Program   : #./forkex3

***************************************************************************/ 
/*--------------------------------------- HEADER FILES ---------------------------------------------*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*-------------------------------------------------------------------------------------------------*/
int main( )
{
 	int pid;
	pid = fork();
	if(pid==0)   /* child process .fork() returns 0 to the child process  on success */
	{      
            	printf("I am the child, my process id is %d\n",getpid( ));
		printf("Child’s parent process id is %d\n",getppid( ));
	
	}	
	else	/* parent process and returns the process ID of the child process to the parent */
	{		
		printf("I am the parents,my  process id is %d\n",getpid( ));
		printf("the parents parent  process id is %d\n",getppid( ));	
		wait(10);
	}
 return 0;
}

