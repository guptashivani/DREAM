#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

#include "files_decl.h"     //header file defining the the packet as a structure

 
 packet *p_obj;
 packet pkt;


int dream( packet *p,float *lat_inter,float *long_inter)
  {
  
  	printf("\n received packet values are");
	printf("\n source latitude is %lf",p->lat_src);
	printf("\n source longitude is %lf",p->long_src);
	printf("\n destination latitude is %lf",p->lat_des);
	printf("\n destination longitude is %lf",p->long_des);

	printf("\n intermediate longitude is %lf",(*long_inter));
	printf("\n intermediate latitude is %lf",(*lat_inter));
  
   	int r=6371;                         /*Radius of earth in KM*/
	float pi;
	double time1;
	float rad_src_lat,rad_src_long,rad_des_lat,rad_des_long,rad_int_lat,rad_int_long; //since math functions take radian values
	float mul;                                                                     
	pi=22/7;
	mul=pi/180;                                               /*multiplication factor to convert degrees into radians*/
	
	printf("\n value of multiplying factor is %lf",mul);
    	float Xs,Ys,Xd,Yd,Xi,Yi,x;                                //for GPS values to convert to xy co-ordinate system
	float dis_int_src;                                         //distance between intermediate and source
    	float angl,Vsd,Mi,dist;
	
	p->t1=clock();                                            //to calculate current time                                        
	time1=p->t1;
	
	rad_src_lat=(p->lat_src)*0.017;                         //conversion  of degrees into radians
	rad_src_long=(p->long_src)*0.017;
	rad_des_lat=(p->lat_des)*0.017;
	rad_des_long=(p->long_des)*0.017;
	rad_int_lat=(*lat_inter)*0.017;
	rad_int_long=(*long_inter)*0.017;
	
	printf("\n value in radians of latitude source is %lf",rad_src_lat);
	printf("\n value in radians of longitude source is %lf",rad_src_long);
	printf("\n value in radians of latitude destination is %lf",rad_des_lat);
	printf("\n value in radians of longitude destination is %lf",rad_des_long);
	printf("\n value in radians of latitude intermediate is %lf",rad_int_lat);
	printf("\n value in radians of longitude intermediate is %lf",rad_int_long);
	printf("\n velocity of des node is %ld", (* p).velo);
	
   	double time_t=(time1-p->t0)/CLOCKS_PER_SEC;     //conversion of clock time in seconds
	
	
    if(time_t>1)
		x=((p->velo)*(time_t));
	else
		x=p->velo;
	
	Xs=r*(cos(rad_src_long))*(sin(90-rad_src_lat));
	Ys=r*(sin(rad_src_long))*(sin(90-rad_src_lat));
	Xd=r*(cos(rad_des_long))*(sin(90-rad_des_lat));
	Yd=r*(sin(rad_des_long))*(sin(90-(rad_des_lat)));
	Xi=r*(cos(rad_int_long))*(sin(90-rad_int_lat));
	Yi=r*(sin(rad_int_long))*(sin(90-rad_int_lat));
	
	printf("\nvalue of velocity is %lf",p->velo);
	
	printf("\ncoordinate value of Xs is %lf",Xs);
	printf("\ncoordinate value of Ys is %lf",Ys);
	printf("\ncoordinate value of Xd is %lf",Xd);
	printf("\ncoordinate value of Yd is %lf",Yd);
	printf("\ncoordinate value of Xi is %lf",Xi);
	printf("\ncoordinate value of Yi is %lf",Yi);
	
	printf("\nmathematical calculations");
	
	Vsd=atan((Yd-Ys)/(Xd-Xs));                        
	dist=sqrt(pow((Xs-Xd),2)+pow((Ys-Yd),2));
	angl=asin(p->velo/dist);
	Mi=atan((Yi-Ys)/(Xi-Xs));
	
	printf("\nangle between src to des is %lf",Vsd);
	
	printf("\ndistance from src to des is %lf",dist);
	
	printf("\nangle is %lf",angl);
	
	printf("\nangle between src to intermediate is %lf",Mi);
	
	printf("\nCHECK THE RANGE OF AN ANGLE");
	
	if(Mi<=(Vsd+angl) && Mi>=(Vsd-angl))
	{
		printf("\nNODE LIES IN THE SECTOR");
		printf("\nNOW FINDING THE DISTANCE");
		dis_int_src=sqrt(pow((Xi-Xs),2)+pow((Yi-Ys),2));
		if(dis_int_src<(dist+x))
		{
			printf("\n the node is in the range");
			
			return 1;
		}
		
		else return 0;
		
	}
	else 
	{
			printf("\nOUT OF RANGE");
		
			return 0;
	}
	
    
    
   }  
