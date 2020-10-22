#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#ifndef TAM_BLOQUE
#define TAM_BLOQUE 1
#endif 

// declarar array para almacenar los bytes leidos
char buff[20480];

int main() {

  int   fdo, fdd,n;
  char  c;

   // mantener este fichero para pruebas iniciales.
  // cambiar por uno mayor para medir tiempos
  fdo = open("/boot/initrd.img-3.2.0-4-amd64", O_RDONLY);

  if( fdo == -1 ) {
    perror("open"); 
    exit(1);
  }

  // Abrir fichero destino para escritura
  fdd = open ("salida.txt", O_RDWR | O_CREAT | O_TRUNC , 0662);
  if (fdd == -1) {
	perror("open"); 
    	exit(1);
  }

  printf("Comienza la copia con TAM_BLOQUE=%d bytes\n", TAM_BLOQUE); 

  // Bucle de copia: leer TAM_BLOQUE btyes por llamada. Escribir lo leido
  while ( (n=read(fdo, buff, TAM_BLOQUE)) > 0 )
  {
  	 if (write(fdd, buff, n ) != n)
     	{
     		perror("Error en write");
	}
  }            

  if (n == -1) 
    perror("read: ");


  close(fdd);
  close(fdo);
  return 0;
}
