#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

// funcion que va leyendo 
// de la entrada estandar byte a byte
// y escribiendo lo leido en la salida 
// estandar (hasta que no se detecte nada 
// en la entrada estandar

//copia lo que se escribe y lo duplica
/*
void copy() {
  char c;
  while(read(0,&c,1)!=0){
      write(1,&c,1);
  }
}
*/
//copia lo que se escribe y lo duplica
void copy() {
  char c;
  while(read(0,&c,1)!=0){
      write(1,&c,1);
  }
}

int main( int argc, char **argv)
{
  int fd;
  char ch;
  
/* Abrir el fichero que se quiere mostrar*/
 fd = open("prueba.txt", O_RDONLY, 0660);

  if( fd == -1 ) { 
    perror("open"); 
    exit(1);
  }

  if(dup2(fd, 0)==-1){
    perror("fallo en dup2");
    exit(EXIT_FAILURE);
  }

/* Hacer lo necesario para que, al llamar 
 a copy, se muestre su contenido por pantalla*/ 

  copy(); 
  return 0;
}
