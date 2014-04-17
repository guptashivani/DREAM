#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <semaphore.h>
#include <files_decl.h>
#include <netinet/in.h>
#define TIME_PORT 5002

void *server_thread(int *);
void *client_thread( packet *);
int dream( packet *,float *,float *);
void *test_func(packet *);




 
 int main()
 {	
 	
 	 packet pkt;
 	int status,ret;
	int test_val;
	int sem_ret;
	float lat_int,long_int;
	printf("\n in main");
	
	
	printf("\n PROGRAM WITH SERVER PORT 5002 STARTED");
 	
	

	pkt.velo=5.0;
	
	if((sem_ret=sem_init(&semaphore02,0,1))<0)
	{
		perror("\nsemaphore error");
		exit(1);
	}
	
	
	int sockfd;
	struct sockaddr_in serv_addr;
	printf("\n creating socket");
	
	
	
	if((sockfd=socket(PF_INET,SOCK_DGRAM,0))<0)
	{
		perror("socket error");
		exit(1);
	}
	
	serv_addr.sin_family=PF_INET;
	serv_addr.sin_port=htons(TIME_PORT);
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	bzero(&(serv_addr.sin_zero),8);
	
	printf("\n binding the socket");
	
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in))<0)
	{
		perror("bind error\n");
		exit(1);
		
	}
	
	pkt.t0=clock();
 	
	pthread_t tid_server;
	if((ret=pthread_create(&tid_server,NULL,&server_thread,&sockfd))<0)
	{
		perror("\nthread error\n");
		exit(1);
	}
	printf("\nreturn value of server func%d",ret);
	
	
	status=pthread_join(tid_server,NULL);
	printf("\nafter join");
	
	if(status<0)
	{
	 	perror("\nthread jion error");
	 	exit(1); 
	}
	}

