#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

 /* Descriptor del fichero */
  int fd;

  // aprteura del fichero de salida
  fd = open("prueba", O_CREAT|O_WRONLY|O_TRUNC, 0660);

  if( fd == -1 ) { 
    perror("open"); 
    exit(1);
  }

 /* Manipular los descriptores de ficheros para que
 la llamada a printf del final se escriba en el fichero 
 (aunque salga tambien por la salida estandar */

 /* Cerramos el fichero, puesto que no podemos usar su
  descriptor de acuerdo al enunciado*/
  close(fd);    

/* Prueba */
  printf("Hola , mundo\n");
}
