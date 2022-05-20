/*************************************************************************

 SourceName         :  forkex2.c                                       
Description           : This program demonstrates the working of a fork() system call.                               


 Compile and execute :                                                               
                To Compile The Program  :  #gcc –o forkex2 forkex2.c
                To Execute The Program   : #./forkex2

***************************************************************************/ 
/*--------------------------------------- HEADER FILES ---------------------------------------------*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/*---------------------------------------************---------------------------------------------*/
int main()
{
	printf("\n Progrem to demonstrate fork() system call functionality. main function printed once \n");  /*Total Number of Processes = 2n , n -number of fork system calls */
	fork();
	fork();
	printf("\n Hello World\n");
	return 0;
}

