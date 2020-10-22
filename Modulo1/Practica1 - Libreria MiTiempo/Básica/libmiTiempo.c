/*
 * @brief: libmiTiempo.c
 * @author: Octavio Sales, Jorge López.
 */

#include "libmiTiempo.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>

/*********************************************DECLARACION DE VARIABLES************************************************/
static struct timespec startc;
static struct timespec stopc;
static struct timeval startg;
static struct timeval stopg;
static int index_clk;
static int opt=0;	//option:[0-2] indica con que funcion se hace la medicion del tiempo.
static double count;	//contador de tiempo
static int paused;	//flag de estado pause
#define true 1
#define false 0
clockid_t clks[] = { CLOCK_REALTIME, CLOCK_MONOTONIC, CLOCK_MONOTONIC_RAW, CLOCK_PROCESS_CPUTIME_ID, CLOCK_THREAD_CPUTIME_ID};

/***********************************************IMPLEMENTACION DE FUNCIONES*********************************************/
int start(){
	int fd;
	char buff[60];
	size_t len;
	/*Apertura del fichero de configuracion */
	if((fd=open("/home/usuarioso/fichconf", O_RDONLY))==-1){
		fprintf(stderr, "miTiempo: open fichconf: %s", strerror(errno));
		//perror("open fichconf ");
		return -1; 
	}
	
	/* Leemos configuracion*/
	if((len=read(fd, buff,30))<=0){
		close(fd);
		fprintf(stderr, "miTiempo: read fichconf: %s", strerror(errno));
		//perror("read fichconf ");
		return -1; 
	}
	char namefoo[14];
	strncpy(namefoo, buff, 13);	//copiamos en una variable la funcion a utilizar.
	if( strcmp(namefoo, "clock_gettime")==0){
		opt=1;			//Definimos como opcion 1: clock_getttime()
		index_clk = (int) (buff[14] - 48);
		int i, ok=0;
		//strncpy(clk, buff, 15);
		/*for(i=0;i<5;i++){
			if(strcmp(clk, clks[i])){
				ok=1;
				index_clk=i;
			}
		}*/
		if(index_clk >=0 && index_clk <5){
		  ok=1;
		}
		if(ok==0){
			close(fd);
			opt=0;
			fprintf(stderr, "miTiempo: fichconfig: bad format. clk_id for clock_getttime() not found.\n");
			return -1; 
		}
		if(clock_gettime(clks[index_clk], &startc)==-1){
			fprintf(stderr, "miTiempo: clock_gettime failed: %s", strerror(errno));
			return -1;
		}
		paused = false;
		count=0;
	}
	else if(strcmp(namefoo, "gettimeofday;")==0){
		opt=2;			//Definimos como opcion 2: gettimeofday()
		if(gettimeofday(&startg, NULL)==-1){
			fprintf(stderr, "miTiempo: gettimeofday failed: %s", strerror(errno));
			return -1;
		}
		paused = false;
		count=0;
	}
	else{
		close(fd);
		fprintf(stderr, "miTiempo: fichconfig: bad format.\n");
		return -1; 
	}
	close(fd);
	return 0;
}

int pause(){
    if(!paused){
	    double ini, fin;
	    if(opt==1){
	      ini = (double) ( ( startc.tv_sec * 1E3) + ( startc.tv_nsec * 1E-6) );
	      clock_gettime(clks[index_clk], &stopc);
	      fin = (double) ( ( stopc.tv_sec * 1E3) + ( stopc.tv_nsec * 1E-6) );
	      count += (int)(fin - ini);
	    }else if(opt==2){
		if(gettimeofday(&stopg, NULL)==-1){
			fprintf(stderr, "miTiempo: gettimeofday failed: %s", strerror(errno));
			return -1;
		}
	      ini= (double) ( ( startg.tv_sec * 1E3) + ( startg.tv_usec * 1E-3) );
	      fin= (double) ( ( stopg.tv_sec * 1E3) + ( stopg.tv_usec * 1E-3) );
	      count += (int)(fin - ini);
	    }else{
	      exit(-1);
	    }
	    paused = true;
    }
    return count;    
}

int resume(){
  if(paused){
    if(opt==1){
	if(clock_gettime(clks[index_clk], &startc)==-1){
		fprintf(stderr, "miTiempo: clock_gettime failed: %s", strerror(errno));
		return -1;
	}
    }else if(opt==2){
	if(gettimeofday(&startg, NULL)==-1){
		fprintf(stderr, "miTiempo: gettimeofday failed: %s", strerror(errno));
		return -1;
	}
    }else{
      exit(-1);
    }
    paused=false;
  }
  return count;
}

int stop(){
	double ini, fin;
	if(opt==1){
		opt=0;
		if(clock_gettime(clks[index_clk], &stopc)==-1){
			fprintf(stderr, "miTiempo: clock_gettime failed: %s", strerror(errno));
			return -1;
		}
		ini= (double) ( ( startc.tv_sec * 1E3) + ( startc.tv_nsec * 1E-6) );
		fin= (double) ( ( stopc.tv_sec * 1E3) + ( stopc.tv_nsec * 1E-6) );
	}
	else if(opt==2){
		opt=0;
		if(gettimeofday(&stopg, NULL)==-1){
			fprintf(stderr, "miTiempo: gettimeofday failed: %s", strerror(errno));
			return -1;
		}
		ini= (double) ( ( startg.tv_sec * 1E3) + ( startg.tv_usec * 1E-3) );
		fin= (double) ( ( stopg.tv_sec * 1E3) + ( stopg.tv_usec * 1E-3) );
	}
	else{
		fprintf(stderr, "miTiempo: hasn't exec start().");
		exit(-1);
	}
	int res= (int)	(count + (fin - ini));
	return res;		
}
