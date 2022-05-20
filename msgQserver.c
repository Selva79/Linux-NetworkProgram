/*************************************************************************

 SourceName         :  msgQserver .c                                      

 Description           : This program accepts the data from the user and puts it into a message 
                                  queue.                                


 Notes :                                                               
                To Compile The Program  :  #gcc –o msgQserver msgQserver.c
                To Execute The Program   : #./msgQserver

***************************************************************************/ 
 
/*--------------------------------------- HEADER FILES ------------------------------------------------*/ 

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h> 

/*-------------------------------------------------------------------------------------------------------------*/

extern int errno;
int msgqid;


#define KEY                            1234L
#define PERMS                       0666
#define MAXMESGDATA    1024
#define MESGHDRSIZE        (sizeof(Mesg) - MAXMESGDATA)   /* Length of   mesg_len  and mesg_type                       */
                                                                                  

typedef struct                                              /* Structure definition                                              */
{                                 
                int mesg_len;                               /* Message length                                                   */
                long mesg_type;                          /* Message type, must be greater than 0  message                                                              */  
                char mesg_data[MAXMESGDATA]; 
}Mesg;


/*-------------------------------------- GLOBAL DECLARATIONS ----------------------------------*/

int server();                                                /* Function prototypes                                              */
void mesg_send();
void *mesg_recv();

/*-------------------------------------------------------------------------------------------------------------*/

int main()                                                   /* Start of main()                                                      */
{
                                                    
              if((msgqid = msgget(KEY,PERMS|IPC_CREAT)) < 0) /* Creating the message 
                                                                                                             queue                              */
                            printf("Server :: Cannot Get The Message Queue, %s",strerror(errno));
               while(1)
               {
                              mesg_recv();                   /* Calling the message receive function               */    
                              mesg_send();                   /* Calling the message send function                   */
                }
                 exit(0);
}

/*------------------------------- FUNCTION DEFINITIONS ------------------------------------------*/

void mesg_send()                                             
{
              Mesg mesg;                                     /* Message structure  object                                 */                       
              {  
                             printf("Enter The Message :");
                             scanf("%s",&mesg.mesg_data);
                             mesg.mesg_type = 1L;    /* Send messages of this type                                */
                             mesg.mesg_len = strlen(mesg.mesg_data) + MESGHDRSIZE;

                              if(msgsnd(msgqid,(char *)&(mesg.mesg_type),mesg.mesg_len,0) != 0)
                              {                                      /* Sending the message                                         */     
                                             printf("Message Send Error, %s\n",strerror(errno));
                                             exit(1);
                               }
            }
}

void *mesg_recv()
{  
              Mesg mesg;                                  /* Message structure object                                     */ 
              int n; 
              mesg.mesg_type = 2L;                 /* Receive messages of this type                             */
              {
                             n = msgrcv(msgqid,(char *)&(mesg.mesg_type),MAXMESGDATA,
                             mesg.mesg_type,0);       /* Receiving the message                                        */
                             if(n <= 0)
                             {
                                           printf("Message Receive Error, %s\n",strerror(errno));
                                           exit(1);
                              }
                              else
                                            printf("Received : %s\n",mesg.mesg_data);
              }
}

/***************************************************************************/
