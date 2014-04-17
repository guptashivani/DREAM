#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>
#include <files_incl.h>    //header file that includes packet structure
#include <malloc.h>      //for dynamic allocation
;
#define SIZE 1024
#define TIME_PORT 5001

void *client_thread(packet *pkt)
{
   
  while(1)
  {  
    	printf("\n in client thread");
	
	int len_size=sizeof(packet);
	int flag;
	
	char *buf=(char *)malloc(len_size);
	printf("\n packet %d",sizeof(packet));
	printf("\n pkt %d",sizeof(pkt));
	
	
	size_t i=0;
	int sock,bytes_sent,len;
	int status;
	
	int count;
	 packet *src_struct_p;
	src_struct_p = pkt;
	
	printf("\n value of packet elements received in client thread");
	printf("\n source lat %lf",src_struct_p->lat_src);
	printf("\n source long %lf",src_struct_p->long_src);
	printf("\n des lat %lf",src_struct_p->lat_des);
	printf("\n des long %lf\n",src_struct_p->long_des);
	printf("\n value of velocity is %lf",src_struct_p->velo);
	printf("\n value of integer is %d",src_struct_p->n);
	printf("\n value of character is %c",src_struct_p->c);
	
	char *src_struct=(char *)src_struct_p;    //character pointer to be sent
	
	
	//converting packet pointer to character structure
	for(count=0;count<len_size;count++)
	{
		buf[count]=src_struct[count];
		
	}
	
	
	struct sockaddr_in client_addr;
	
	printf("\ncreating client socket");
	
	if((sock=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("socket error");
		exit(1);
	}
	
	printf("\n initializing client structure");
	
	client_addr.sin_family=AF_INET;
	client_addr.sin_port=htons(5002); 
	client_addr.sin_addr.s_addr=inet_addr("192.168.127.255");
	bzero(&(client_addr.sin_zero),8);
	time_t t0=clock();
	
	printf("\nBEFORE SENDTO");
	len=sizeof(packet);
	
	if((bytes_sent=sendto(sock,buf,len,0,(struct sockaddr_in*)&client_addr,sizeof(struct sockaddr_in)))<0)
		{
			perror("error in sending\n");
			
		}
	
	else
	{
		printf("\nmsg sent\n");
	}
	printf("\n BYTES SENT %d",bytes_sent);	  
	
	printf("\n BEFORE CLIENT SLEEPS");
	printf("\n going back to temp");
	
	return;
	sleep(10);
	
 }
}
