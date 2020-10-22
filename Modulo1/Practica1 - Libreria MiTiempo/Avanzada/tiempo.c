/*
 * @brief: libmiTiempo.c
 * @author: Octavio Sales, Jorge López.
 */

#include "tiempo.h"
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
static int index_clk;
static int opt=0;	//option:[0-2] indica con que funcion se hace la medicion del tiempo.
static const clockid_t clks[] = { CLOCK_REALTIME, CLOCK_MONOTONIC, CLOCK_MONOTONIC_RAW, CLOCK_PROCESS_CPUTIME_ID, CLOCK_THREAD_CPUTIME_ID};
static int index_timeid=1;	// indice de id's de contador.

/***********************************************IMPLEMENTACION DE FUNCIONES*********************************************/
mi_timeid_t createaCounter() {
	mi_timeid_t t;
	t.id= index_timeid;
	t.counter=0;
	t.started=false;
	t.paused=false;
	t.clock_get.tv_sec=0;
	t.clock_get.tv_nsec=0;
	t.gettime.tv_sec=0;
	t.gettime.tv_usec=0;
	index_timeid++;
	return t;
}  
  
int start( mi_timeid_t* t ){
    if(t->id < 1 || t->id > index_timeid){
	  fprintf(stderr, "miTiempo: mi_timeid %d: doesn't exist.\n", t->id);
	return -1;
    }
	int fd;
	char buff[60];
	size_t len;
	/*Apertura del fichero de configuracion */
	if((fd=open("/home/usuarioso/fichconf", O_RDONLY))==-1){
		fprintf(stderr, "miTiempo: open fichconf: %s\n", strerror(errno));
		//perror("open fichconf ");
		return -1; 
	}
	
	/* Leemos configuracion*/
	if((len=read(fd, buff,30))<=0){
		close(fd);
		fprintf(stderr, "miTiempo: read fichconf: %s\n", strerror(errno));
		//perror("read fichconf ");
		return -1; 
	}
	char namefoo[14];
	strncpy(namefoo, buff, 13);	//copiamos en una variable la funcion a utilizar.
	if( strcmp(namefoo, "clock_gettime")==0){
		opt=1;			//Definimos como opcion 1: clock_getttime()
		index_clk = (int) (buff[14] - 48);
		int i, ok=0;
		if(index_clk >=0 && index_clk <5){  //Si clockid_t es valido.
		  ok=1;
		}
		if(ok==0){
			close(fd);
			opt=0;
			fprintf(stderr, "miTiempo: fichconfig: bad format. clk_id for clock_getttime() not found.\n");
			return -1; 
		}
		if(clock_gettime(clks[index_clk], &t->clock_get)==-1){
			fprintf(stderr, "miTiempo: mi_timeid %d: clock_gettime failed: %s\n", t->id, strerror(errno));
			return -1;
		}
		//printf("fichconf: clock_gettime(%s).\n", clks[index_clk]);
	}
	else if(strcmp(namefoo, "gettimeofday;")==0){
		opt=2;			//Definimos como opcion 2: gettimeofday()
		if(gettimeofday(&t->gettime, NULL)==-1){
			fprintf(stderr, "miTiempo: mi_timeid %d: gettimeofday failed: %s\n", t->id, strerror(errno));
			return -1;
		}
	}
	else{
		close(fd);
		fprintf(stderr, "miTiempo: fichconfig: bad format.\n");
		return -1; 
	}
	close(fd);
	t->paused = false;
	t->started = true;
	t->counter= 0;
	return 0;
}

int pause( mi_timeid_t* t ){
    if(t->id < 1 || t->id > index_timeid){
	  fprintf(stderr, "miTiempo: mi_timeid %d: doesn't exist.\n", t->id);
	return -1;
    }
    if(!t->paused && t->started){
	    double ini, fin;
	    if(opt==1){
		ini = (double) ( (t->clock_get.tv_sec * 1E3) + ( t->clock_get.tv_nsec * 1E-6) );
		if(clock_gettime(clks[index_clk], &t->clock_get)==-1){
			fprintf(stderr, "miTiempo: mi_timeid %d: clock_gettime failed: %s\n", t->id, strerror(errno));
			return -1;
		}
	      fin = (double) ( ( t->clock_get.tv_sec * 1E3) + ( t->clock_get.tv_nsec * 1E-6) );
	      t->counter = t->counter + (fin - ini);
	    }else if(opt==2){
		 ini= (double) ( ( t->gettime.tv_sec * 1E3) + ( t->gettime.tv_usec * 1E-3) );
		if(gettimeofday(&t->gettime, NULL)==-1){
			fprintf(stderr, "miTiempo: mi_timeid %d: gettimeofday failed: %s\n", t->id, strerror(errno));
			return -1;
		}
	     
	      fin= (double) ( ( t->gettime.tv_sec * 1E3) + ( t->gettime.tv_usec * 1E-3) );
	      t->counter = t->counter + (fin - ini);
	    }else{
	      return -1;
	    }
	    t->paused = true;
    }
    return 0;  
}

int resume( mi_timeid_t* t ){
   if(t->id < 1 || t->id > index_timeid){
	  fprintf(stderr, "miTiempo: mi_timeid %d: doesn't exist.\n", t->id);
	return -1;
    }
      if(t->paused && t->started){
	if(opt==1){
	    if(clock_gettime(clks[index_clk], &t->clock_get)==-1){
			fprintf(stderr, "miTiempo: mi_timeid %d: clock_gettime failed: %s\n", t->id, strerror(errno));
		    return -1;
	    }
	}else if(opt==2){
	    if(gettimeofday(&t->gettime, NULL)==-1){
			fprintf(stderr, "miTiempo: mi_timeid %d: gettimeofday failed: %s\n", t->id, strerror(errno));
		    return -1;
	    }
	}else{
	  return -1;
	}
	t->paused=false;
      }
      return 0;
}

int stop( mi_timeid_t* t ){
	if(t->id < 1 || t->id > index_timeid){
	  fprintf(stderr, "miTiempo: mi_timeid %d: doesn't exist.\n", t->id);
	  return -1;
	}
	if(t->paused){
	  t->started=false;
	  t->paused=false;
	  return 0;
	}
	if(!t->started){
		fprintf(stderr, "miTiempo: mi_timeid %d: hasn't exec start().\n", t->id);
	  return -1;
	}
	double ini, fin;
	if(opt==1){
		ini= (double) ( ( t->clock_get.tv_sec * 1E3) + ( t->clock_get.tv_nsec * 1E-6) );
		if(clock_gettime(clks[index_clk], &t->clock_get)==-1){
			fprintf(stderr, "miTiempo: mi_timeid %d: clock_gettime failed: %s\n", t->id, strerror(errno));
			return -1;
		}		
		fin= (double) ( ( t->clock_get.tv_sec * 1E3) + ( t->clock_get.tv_nsec * 1E-6) );
	}
	else if(opt==2){
		ini= (double) ( ( t->gettime.tv_sec * 1E3) + ( t->gettime.tv_usec * 1E-3) );
		if(gettimeofday(&t->gettime, NULL)==-1){
			fprintf(stderr, "miTiempo: mi_timeid %d: gettimeofday failed: %s\n", t->id, strerror(errno));
			return -1;
		}
		fin= (double) ( ( t->gettime.tv_sec * 1E3) + ( t->gettime.tv_usec * 1E-3) );
	}
	else{
		fprintf(stderr, "miTiempo: mi_timeid %d: hasn't exec start().\n", t->id);
		return -1;
	}
	t->counter = t->counter + (fin - ini);
	t->started=false;
	t->paused=false;
	return 0;		
}
