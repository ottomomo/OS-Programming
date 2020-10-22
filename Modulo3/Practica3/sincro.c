#include <sys/types.h>
/*
 * @brief: daemon sincro
 * @author: Octavio Sales y Jorge López
 */

#include <sys/stat.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include "copia.h"
#include <errno.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <signal.h>
#include <syslog.h>
#include <sys/time.h>

#include "event_queue.h"
#include "inotify_utils.h"

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * EVENT_SIZE )

int keep_running;		// flag de ejecuccion
char *diro;			// Directorio Origen
char *dird;			// Directorio Destino
struct itimerval timer; 	// Temporizador de Alarma
int inotify_fd; 		// Descriptor de Fichero inotify
extern int count_events;	// Contador de eventos
queue_t q;			// Cola de eventos



/* Lectura del Fichero de Configuracion .sincro.conf */
void config(){
  
  FILE* fd;
  ssize_t len;
  diro=NULL;
  dird=NULL;
  size_t n = 0;
  char path[256];
  char *home;
  home = getenv("HOME");
  strcpy(path, home);
  int length;
  length =  strlen(path);
  path[length]='\0';
  strcat(path, "/.sincro.conf");
  /*Apertura del fichero de configuracion */
  if((fd=fopen(path, "r"))== NULL){
	fprintf(stderr, "sincro : error open sincro.conf: %s\n", strerror(errno));
	//perror("open fichconf ");
	exit(-1); 
  }
  
  /*Lectura de Directorio Origen */
  if ( (len= getline(&diro, &n, fd)) == -1){
      fprintf(stderr, "sincro : error read origen in sincro.conf: %s\n", strerror(errno));
      exit(-1);				
  }
  diro[len-1]='\0'; //salto de linea
  
   
  /*Lectura de Directorio Destino */
  if ( (len= getline(&dird, &n, fd)) == -1){
      fprintf(stderr, "sincro : error read destino in sincro.conf: %s\n", strerror(errno));
      exit(-1);				
  }
  dird[len-1]='\0'; //salto de linea

  /*Compruebo que existe el directorio origen*/
  DIR *pdiro;
  pdiro=NULL;
  if ( ( pdiro=opendir (diro) )== NULL ){
    perror("opendir origen");
    exit(-1);
  }
  closedir(pdiro);
  printf("sincro: dir origen: %s .\n", diro);
   
  /*Si no existe el directorio destino, lo crea*/
  if (opendir (dird) == NULL){
    mkdir (dird, 0700);
    printf("sincro: dir destino created: %s .\n", dird);
  }else{
    printf("sincro: dir destino: %s .\n", dird);
  }

  /*Lectura de Tiempo de Alarma */
  char *t;
  t=NULL;
  len=0;
  if ( (len= getline(&t, &n, fd)) == -1){
      fprintf(stderr, "sincro : error read time in sincro.conf: %s\n", strerror(errno));
      exit(-1);				
  }
  len = strlen(t);
  int time;
  time=0;
  time=atoi(t);
  printf("sincro: timer: %d s.\n", time);
  timer.it_value.tv_sec = time;
  timer.it_value.tv_usec = 0;
  timer.it_interval.tv_sec = time;
  timer.it_interval.tv_usec = 0;

  fclose(fd);
  printf("sincro: Config completed.\n");
}
      /* funcion que hace un syslog de los eventos procesados */
void do_log(){
   syslog(LOG_NOTICE, "daemon sincro: %d events handled.", count_events);
}

	  /* Manejador de señal Alarma */
void catch_alarm(){
  
  syslog(LOG_NOTICE, "daemon sincro: catch signal ALARM.");
  do_log();
  count_events=0;
}
 /* Manejador de señal USR1 */
void catch_usr1(){
  syslog(LOG_NOTICE, "daemon sincro: catch signal USR1.");
  do_log();
}
 
	  /* Manejador de señal HangUp */
void catch_hup(){
  syslog(LOG_NOTICE, "daemon sincro: catch signal HangUp.");
  /* Borramos la cola de eventos*/
  queue_destroy (q);
    /* Cerramos inotify_fd */
  close_inotify_fd (inotify_fd);
  /* Leemos nueva Conf */
  config();
  /* Inicialice a inotify */
  if((inotify_fd = open_inotify_fd ())<0){
    syslog(LOG_NOTICE, "daemon sincro: error in open_inotify_fd.");
    exit(EXIT_FAILURE);
  }
  /* Añadimos a inotify el Directorio */
  int wd;
  if((wd = watch_dir (inotify_fd, diro, IN_MODIFY | IN_ATTRIB | IN_DELETE | IN_CREATE ))<0){
      syslog(LOG_NOTICE, "daemon sincro: error in watch_dir.");
    exit(EXIT_FAILURE);
  }
  /*Creacion de la cola de eventos */
  q = queue_create (128);
}
	  /* Manejador de señal Terminar */
void catch_term(){
  
    syslog(LOG_NOTICE, "daemon sincro: catch signal TERM.");
    keep_running = 0;
    char path[256];
    char *home;
    home = getenv("HOME");
    strcpy(path, home);
    int length;
    length =  strlen(path);
    path[length]='\0';
    strcat(path, "/.sincro.lock");
    if((unlink(path)) == -1)
	  fprintf(stderr, "Sincro: couldn't delete file sincro.lock ...\n");
    
    /* Borramos la cola de eventos*/
    queue_destroy (q);
    /* Cerramos inotify_fd */
    close_inotify_fd (inotify_fd);
    syslog (LOG_NOTICE, "daemon sincro terminated.");
    closelog();
    exit(EXIT_SUCCESS);
}

	    /* Añade una rutina a una señal*/
void * ini_manejador(int signal, void *manejador)
{
    struct sigaction act;
    struct sigaction old_act;

    act.sa_handler = manejador;

    sigemptyset(&act.sa_mask);

    act.sa_flags = SA_RESTART;

    sigaction(signal, &act, &old_act);
}

		/* Demoniza el Proceso */
void daemonize() {
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();
    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);
    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);
    
    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);
    
    /* Fork off for the second time*/
    pid = fork();
    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);
    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);
    
    /* Creacion de Fichero .sincro.lock */
    char path[256];
    char *home;
    home = getenv("HOME");
    strcpy(path, home);
    strcat(path, "/.sincro.lock");
    int len;
    len =  strlen(path);
    path[len]='\0';
    FILE* fdl;
    //char pids [5];
    int p=getpid();
    //memset(pids, 0, sizeof pids);/*Limpia el array*/
    if( (fdl=fopen(path, "w+")) == NULL){
	syslog(LOG_NOTICE, "ERROR: create sincro.lock.");
	exit(EXIT_FAILURE);
    }
    fprintf(fdl, "%d", p);
    fclose(fdl);
    
    /* Set new file permissions */
    umask(0);
    /* Change the working directory to the root directory */
     chdir("/");
     /* Close FD's */
     close(STDIN_FILENO);
     close(STDOUT_FILENO);
     close(STDERR_FILENO);
     stdin = fopen("/dev/null", "r");
     stdout = fopen("/dev/null", "w+");
     stderr = fopen("/dev/null", "w+");
     /* Open the log file */
    openlog ("sincro", LOG_PID, LOG_DAEMON);
}  

int main() {
  
  int wd;
  keep_running = 1;
  umask(0);
  
  /* Comprobamos si ya existe el Fichero .sincro.lock */
  char path[256];
  char *home;
  home = getenv("HOME");
  strcpy(path, home);
  strcat(path, "/.sincro.lock");
  int len;
  len =  strlen(path);
  path[len]='\0';
  FILE* fdl;
  char pid [5];
  if( (fdl=fopen(path, "r")) != NULL){
     fgets(pid, 5, fdl);
     fprintf(stderr, "ERROR: sincro.lock already exists. Daemon Sincro is running by pid: %s\n", pid);
     fclose(fdl);
     return -1;
  }

   /* Lectura de .sincro.conf */
   config();
  
  /* Inicialice a inotify */
  if((inotify_fd = open_inotify_fd ())<0){
    return -1;
  }
  

  /* Añadimos a inotify el Directorio */
  if((wd = watch_dir (inotify_fd, diro, IN_MODIFY | IN_ATTRIB | IN_DELETE | IN_CREATE ))<0){
    fprintf(stderr, "sincro: Error en watch_dir()\n");
    return -1;
  }
  
  
  /* Inicializar el manejador de SIGALRM, etc... con la funcion catch_alarm(), etc... */  
  ini_manejador(SIGALRM,catch_alarm);
  ini_manejador(SIGTERM,catch_term);
  ini_manejador(SIGHUP, catch_hup);
  ini_manejador(SIGUSR1, catch_usr1);
  
  
  /* Creamos el cjto de señales a procesar */
  sigset_t seniales;
  sigfillset(&seniales);  // crea un conjunto con todas las señales
  sigdelset(&seniales,SIGUSR1);
  sigdelset(&seniales,SIGHUP);
  sigdelset(&seniales,SIGALRM);
  sigdelset(&seniales,SIGTERM);
  sigprocmask(SIG_BLOCK,&seniales,NULL); 	// bloqueamos todas la señales, excepto las pertinentes...
  printf("creating the daemon.\n");
  
  /* Creacion del Demonio */
   daemonize();
   syslog(LOG_NOTICE, "daemon sincro created.");
   
   /*Creacion de la cola de eventos */
  q = queue_create (128);
  
 
  
  while(1){
    
    /* Inicializar el timer para la señal Alarma mediante setitimer */
    if(setitimer (ITIMER_REAL, &timer, NULL) == -1){
	    //perror("seettimer");
	    syslog(LOG_NOTICE, "daemon sincro: setitimer() failed.");
    }
     /* Procesamos los eventos registrados */
    process_inotify_events (q, inotify_fd);
    /* Suspendemos el proceso a la espera de la señal pertinente */
    syslog(LOG_INFO, "daemon sincro suspended.");
    sigsuspend(&seniales);
    
  }
  
  return 0;
}
