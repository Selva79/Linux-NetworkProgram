/*************************************************************************

 SourceName         :  msgQclient.c                                       

 Description           : This program reads the data from the message queue and displays it.                                


 Notes :                                                               
                To Compile The Program  :  #gcc –o msgQclient msgQclient.c
                To Execute The Program   : #./msgQclient

***************************************************************************/ 
 
/*------------------------------------------ HEADER FILES ---------------------------------------------*/

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


int client();
void mesg_send();
void *mesg_recv();
void handler();


int main()                                                   /* Start of main()                                                      */
{
              if((msgqid = msgget(KEY,0)) < 0)  /* Open the message queue                                 */
                            printf("Client :: Cannot Get Message Queue, %s",strerror(errno));

              while(1)
              {
                             mesg_send();                /* Calling the send function                                     */     
                             mesg_recv();                 /* Calling the receive function                                 */         
              }

              exit(0);
}

/*----------------------------------- FUNCTIONDECLARATIONS -----------------------------------*/

void mesg_send()
{


              Mesg mesg;                                  /* Message structure object                                     */
              {  
                           printf("Enter The Message :");
                           scanf("%s",&mesg.mesg_data);
                           mesg.mesg_type = 2L;    /* Send messages of this type                                  */
                           mesg.mesg_len = strlen(mesg.mesg_data) + MESGHDRSIZE;
                           if(msgsnd(msgqid,(char *)&(mesg.mesg_type),mesg.mesg_len,0) != 0)
                           {       
                                          printf("Message Send Error, %s\n",strerror(errno));
                                          exit(1);
                            } 
                }
}

void *mesg_recv()
{  
              Mesg mesg;                                 /* Message structure object                                      */
              int n; 
              mesg.mesg_type = 1L;                /* Receive messages of this type                              */
              signal(SIGINT,handler);              /* Setting the signal                                                 */
{
                            n = msgrcv(msgqid,(char *)&(mesg.mesg_type),MAXMESGDATA,
                            mesg.mesg_type,0);
                            if(n < 0)
                            {
                                           printf("Message Receive Error, %s\n",strerror(errno));
                                           exit(1);
                            } 
                            else
                                          printf("Received: %s\n",mesg.mesg_data);
              }
}

void handler()                                           /* Signal handler function                                        */                        
{
             static int flag = 1;
             if(flag) 
            {
                           if(msgctl(msgqid,IPC_RMID, 0) < 0)  /* Remove the
                                                                                                                 the message queue     */   
                                         printf("Error In Removing Message Queue, %s\n",strerror(errno)); 
                            else
                                         printf("Message Queue Successfully Removed\n");     
                            flag = 0;
             }
             exit(0);
}
/***************************************************************************/
