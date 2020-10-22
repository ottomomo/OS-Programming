#include <sys/types.h>
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

#include "event_queue.h"
#include "inotify_utils.h"

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * EVENT_SIZE )

int keep_running;// flag de continue
char *diro;	//Directorio Origen
char *dird;	//Directorio Destino

/* Signal handler that simply resets a flag to cause termination */
void signal_handler (int signum)
{
  keep_running = 0;
}

int main() {
  
  FILE* fd;
  ssize_t len;
  diro=NULL;
  dird=NULL;
  int fdo, fdd;
  int inotify_fd, wd;
  keep_running = 1;
  size_t n = 0;
  
  /* Set a ctrl-c signal handler */
  if (signal (SIGINT, signal_handler) == SIG_IGN)
  {
      /* Reset to SIG_IGN (ignore) if that was the prior state */
      signal (SIGINT, SIG_IGN);
  }

  /*Apertura del fichero de configuracion */
  if((fd=fopen("/home/usuarioso/practica2/.sincro.conf", "r"))== NULL){
	fprintf(stderr, "sincro : open sincro.conf: %s\n", strerror(errno));
	//perror("open fichconf ");
	return -1; 
  }

  /*Lectura de Directorio Origen */
  if ( (len= getline(&diro, &n, fd)) == -1){
      fprintf(stderr, "sincro : read sincro.conf: %s\n", strerror(errno));
      return -1;				
  }
  diro[len-1]='\0'; //salto de linea
  
  /*Lectura de Directorio Destino */
  if ( (len= getline(&dird, &n, fd)) == -1){
      fprintf(stderr, "sincro : read sincro.conf: %s\n", strerror(errno));
      return -1;				
  }
  dird[len-1]='\0'; //salto de linea

  /*Compruebo que existe el directorio origen*/
  char *pdiro;
  if ( ( pdiro=opendir (diro) )== NULL ){
    perror("opendir origen");
    exit(-1);
  }

  /*Si no existe el directorio destino, lo crea*/
  if (opendir (dird) == NULL)
    mkdir (dird, 0700);

  /* Inicialice a inotify */
  if((inotify_fd = open_inotify_fd ())<0){
    return -1;
  }
  
  /*Creacion de la cola de eventos */
  queue_t q;
  q = queue_create (128);

  /* Añadimos a inotify el Directorio */
  if((wd = watch_dir (inotify_fd, diro, IN_MODIFY | IN_ATTRIB | IN_DELETE | IN_CREATE ))<0){
    //if((wd = watch_dir (inotify_fd, diro, IN_ALL_EVENTS))<0){
    printf("Error en watch_dir\n");
    return -1;
  }

  /* Procesamos los eventos registrados */
  process_inotify_events (q, inotify_fd);
  
  /* Cerramos inotify_fd y borramos la cola de eventos*/
  close_inotify_fd (inotify_fd);
  queue_destroy (q);
   
  return 0;
}
