#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <semaphore.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/time.h>
#include <files_incl.h>

#define SIZE 1024


void *client_thread(packet *);  //declaration of client thread function
 packet *pkt_recv;
pthread_t tidc;                 //client thread id


void *server_thread(int *sock)
{
  while(1)
  {
  int flag;
  printf("\n entered server");
  float lat_int,long_int;
  	
  	int status,len;
	socklen_t addrlen;
	printf("\nINSIDE SERVER 5001");
	char *buf=(char *)malloc(196);   //dynaic allocation of character buffer that receives the packet
	struct sockaddr_in client_addr;
  	
	int recv_bytes,y;
	
	sem_post(&semaphore01);
	
	len=sizeof( buf);
	
	printf("\n******receiving the packet");
	printf("\nmsg recv");
	
	//sem_wait(&semaphore01);
  	
	
		if((recv_bytes=recvfrom((*sock),buf,196,0,(struct sockaddr_in *)&client_addr,&addrlen))<0)
		{
			perror("recv error\n");
			exit(1);
			
		}
		
	
	
	printf("\n received the msg");
	printf("\n received the msg");
	printf("\n received the msg");
		//printf("\nprocessing");
	 packet *t=(packet *)buf;
	 packet *content;
	 content=(char *)malloc(sizeof(packet));
	 
	 for(flag=0;flag<196;flag++)
	{
		content[flag]=t[flag];
	}
	
	
		printf("\nvalue of lat is %lf",content->lat_src);
		printf("\nvalue of long is %lf",content->long_src);
		printf("\nvalue of lat is %lf",content->lat_des);
		printf("\nvalue of long is %lf",content->long_des);
		printf("\nvalue of velocity is %lf",content->velo);
		printf("\nvalue of ip src is %s",content->ip_src);
		printf("\nvalue of ip des is %s",content->ip_des);
		printf("\nmsg received is %s",content->msg);
		printf("\ninteger received is %d",content->n);
		printf("\ncharacter received is %c",content->c);
	if(content->ip_src==client_addr.sin_addr.s_addr)
	{
		printf("abort message\n");
	}
	/*y=(dream_algom(&pkt_recv,lat_int,long_int));
	if(y==1)
	{
	 printf("hello");
	}*/
	else{
	printf("\nenter the value of intermediate latitude\n");
	scanf("%lf",&lat_int);
	
	printf("\nserver");
	printf("\nenter the value of intermediate longitude\n");
	scanf("%lf",&long_int);
	
	printf("\napplying the dream algo");
	if((y=dream(content,lat_int,long_int))==1)
	{
		pthread_t tid_c2;
		pthread_create(&tid_c2,NULL,client_thread,content);
		status=pthread_join(tid_c2,NULL);
		
	}
	}
	sem_post(&semaphore01);
	
	sleep(20);
  }
}

