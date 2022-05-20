/*************************************************************************

 SourceName         :  semaphoreex.c                                       

 Description           : This program demonstrates the use of the semaphore for IPC synchronization.                                


 Notes :                                                               
                To Compile The Program  :  #gcc –o semaphoreex semaphoreex.c
                To Execute The Program   : #./semaphoreex

***************************************************************************/ 
 
/*------------------------------------------- HEADER FILES -------------------------------------------*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>


/*-------------------------------------------------------------------------------------------------------------*/

extern int errno;


#define SEMKEY 0x20                              /* Semaphore key                                                     */
#define PERMS  0666                              /* Permission flag                                                      */


int main()                                                  
{
              int semid,pid;
              struct sembuf sop;
              semid = semget(SEMKEY,1,IPC_CREAT|PERMS);                           /* Create  semaphore        */
              if(semid < 0)
                            printf(" Error In creating Semaphore: %s",strerror(errno));
              semctl(semid,0,SETVAL,1);                                         /* Set value to 1             */
              pid = fork();
              if(pid == 0)                                   /* Child process                                                       */
              {
                        printf("Child process:: before semop\n");
                        sop.sem_num = 0;
                        sop.sem_op = -1;                               /* Wait untill the value is greater than or equal to 1 and lock the semaphore                                       */
                                                                       
                        sop.sem_flg = 0; 
                        semop(semid,&sop,1);

                         printf("Child :: Semaphore Locked\n");
                         printf("Child :: Entering Critical Section\n");
                         sleep(2);                               
                         printf("Child :: Leaving Critical Section\n");
                         printf("Child :: Releasing Semaphore\n");
                         sop.sem_num = 0;
                         sop.sem_op =  1;                             /* Add 1 to the current semaphore value                 */
                         sop.sem_flg = 0;
                         semop(semid,&sop,1);                        /* Release the semaphore                                         */
              }
              else
              {
                            printf("Parent :: Before semop\n");
                            sop.sem_num = 0;
                            sop.sem_op = -1;                                   /* Wait untill the value is greater than or equal to 1 and lock the semaphore           */

                            sop.sem_flg = 0; semop(semid,&sop,1);                  
                            printf("Parent :: Semaphore Locked\n");
                            printf("Parent :: Entering Critical Section\n");
                            sleep(2);
                            printf("Parent :: Leaving Critical Section\n");
                            printf("Parent :: Releasing Semaphore\n");
                            sop.sem_num = 0;
                            sop.sem_op =  1;            /* Add 1 to current semaphore value                       */
                            sop.sem_flg = 0;                       
                            semop(semid,&sop,1);    /* Release semaphore                                             */
                            wait(0);                            /* Wait for the child to terminate                           */   

                            if(semctl(semid,0,IPC_RMID,0) < 0)    /* Remove the semaphore               */
                                         printf("Parent :: Error In Removing The Sempahore, %s\n", 
                                                    strerror(errno));
                            else
                                          printf("Parent :: Semaphore Removed Successfully\n");   
                            exit(0);
              }
}
/***************************************************************************/
