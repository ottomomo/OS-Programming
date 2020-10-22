#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//#define stdout


int main() {

 /* Descriptor del fichero */
  int fd;

  // aprteura del fichero de salida
  fd = open("prueba.txt", O_CREAT|O_WRONLY|O_TRUNC, 0660);

  if( fd == -1 ) { 
    perror("open"); 
    exit(1);
  }

 /* Manipular los descriptores de ficheros para que
 la llamada a printf del final se escriba en el fichero 
 (aunque salga tambien por la salida estandar */
 
 //dup duplica un descriptor de archivo, fildes, enviando un nuevo descriptor.
 /*
   if(dup2(fd, STDOUT_FILENO)==-1){
     perror("fallo el dup2");
     exit(EXIT_FAILURE);
   }
*/
 //dup2 copia eficazmente un descriptor de archivo a otro especificando qué descriptor usar para la copia.
  close(1);
  dup(fd);
  /*
  if(dup2(fd, STDOUT_FILENO)==-1){
    perror("fallo en dup2");
    exit(EXIT_FAILURE);
  }
 /* Cerramos el fichero, puesto que no podemos usar su
  descriptor de acuerdo al enunciado*/
  close(fd);    

/* Prueba */
  printf("Hola , mundo\n");
}
