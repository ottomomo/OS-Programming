#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

/* Definicion de los descriptores */

  int  fd1, fd2;
  FILE *fp;

/* Apertura del fichero solo lectura */

  fd1 = open("/etc/motd",O_RDONLY );

/* Comprobacion de errores */
  if (fd1 == -1) {
    perror("open");
    exit(1);
  }

/* Ejemplo de creacion de fichero con permisos rw para ugo*/
  fd2 = open("salida", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXG);

/* Comprobacion de errores */
  if (fd2 == -1) {
    perror("open"); 
    exit(1);
  }
/*
   ..........
   
   Uso de los Descriptores
*/
  fp = fopen ( "a.c", "r" );        
  if (fp==NULL) {fputs ("File error",stderr); exit (1);}
  fclose ( fp );

  return 0;

/* Cierre de los ficheros */
  close(fd1);
  close(fd2);
}
