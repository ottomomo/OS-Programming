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
  fdo = open("/etc/motd", O_RDONLY);

  if( fdo == -1 ) {
    perror("open"); 
    exit(1);
  }

  // Abrir fichero destino para escritura
  fdd = open ("/boot/initrd.img-3.2.0-4-amd64", O_WRONLY/*|O_SYNC*/);
  if (fdd == -1) {
	perror("open"); 
    	exit(1);
  }

  printf("Comienza la copia con TAM_BLOQUE=%d bytes\n", TAM_BLOQUE); 
  // Incluir las llamadas de temporizacion de vuestra libreria (start...)
//	 double t_ini, t_fin;
//	 struct timespec tv_ini, tv_fin;
//	 clock_gettime(CLOCK_PROCESS_CPUTIME_ID , &tv_ini);
  // Bucle de copia: leer TAM_BLOQUE btyes por llamada. Escribir lo leido
  while ( (n=read(fdo, buff, TAM_BLOQUE)) > 0 )
  {
  	 if (write(fdd, buff, TAM_BLOQUE ) != TAM_BLOQUE)
     	{
     		perror("Error en write");
	}
  }            
//	clock_gettime(CLOCK_PROCESS_CPUTIME_ID , &tv_fin); 
//	t_ini =(double) ( tv_ini.tv_sec + ( tv_ini.tv_nsec * 1E-9) );
//	t_fin =(double) ( tv_fin.tv_sec + ( tv_fin.tv_nsec * 1E-9) );    

  if (n == -1) 
    perror("read: ");

//  printf("tiempo de inicio: %d\n", t_ini);
//  printf("tiempo de fin: %d\n",t_fin );
  close(fdd);
  close(fdo);
  return 0;
}
