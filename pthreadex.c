/***************************************************************************************

 SourceName           :  pthreadex.c                                       
Description           : This program demonstrates the working of a simple thread.                                


 Notes :                                                               
                To Compile The Program  :  #gcc -o pthreadex pthreadex.c –lpthread
                To Execute The Program   : #./pthreadex

*****************************************************************************************/ 
 
/*-------------------------------------- HEADER FILES -------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

/*-------------------------------------------------------------------------------------------------------------*/
char message1[] = "pthread 1";  
char message2[] = "pthread 2";          

/*---------------------------------- FUNCTION DEFINITION -----------------------------------------*/

void *thread_function1(void *arg)                  /* Thread function definition                                   */
{
           int count=0;
          while(count<5)
	  {	 
	      count++; 
              printf("Thread Functionc1 is running . The Argument is %s\n",(char *)arg);
              sleep(1);
              
	  }
	  pthread_exit(" Thread1 exit\n");  
}



void *thread_function2(void *arg)                  /* Thread function definition                                   */
{
           int count=0;
	    while(count<5)
	    {
	      count++;
              printf("Thread function 2 Is Running. The Argument is %s\n",(char *)arg);
              sleep(1);
              
	    }
	     pthread_exit("Thread 2 exit \n");  
}



int main()   
{                                                
              int retVal;
              pthread_t a_thread, b_thread;              /* pthread object                                                       */
              void *thread_result;                       /* Pointer to result                                                    */  

              retVal = pthread_create(&a_thread,NULL,thread_function1,(void *)message1);         /* Creating a thread 1    */
                                                                   
             if(retVal != 0)
             {
                            perror("Thread Creation Failed\n");
                            exit(EXIT_FAILURE);
             }
	     pthread_create(&b_thread,NULL,thread_function2, message2);                    /* Creating a thread 1    */

             printf("Waiting For Thread1 and Thread 2 to finish...\n");

             retVal = pthread_join(a_thread,NULL);                                       /* Waiting for the thread to join back  the main thread    */ 
                                                                                                
             pthread_join(b_thread,NULL);  
	     if(retVal != 0) 
               {
                               perror("Thread Join Failed\n");
                               exit(EXIT_FAILURE);
               } 
            
               printf("Thread joined \n");
               exit(EXIT_SUCCESS);
}
    

/******************************************************************************************************/
