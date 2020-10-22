#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[]) {
 
 int fd;
 struct stat buf;
 size_t mapSize;
 char* texto;
 int i;
 if (argc!=2 || argv[1]==NULL) {
    printf("Error. Uso: ./mmap nomFich\n");
    exit(-1);
 }

 if(  ( fd = open(argv[1], O_RDWR)) == -1) {
 	perror("Fallo en open");
	exit(-1);
 }

 // 1.Usar fstat para obtener informacion del fichero  
 if  (fstat(fd,&buf) == -1) {
	perror("Fallo en fstat");
	close(fd);
	exit(-1);
 }  
 // 2. comprobar que es un fihcero regular 

 // 3. Obtener el tamano del fichero 

 mapSize = ... ; // minimo entre 100 y tamano fichero

 // 4. Usar mmap para volcar los bytes en memroia 
 if ( ( texto= mmap(.....)) ==-1 ) { 
 	......
  }

 // 5. paso a mayusculas. El codigo ASCII de las minusculas va de 97 a 122
 // El de las mayusculas, es el mismo codigo ASCII -32
  for (i=0;i<mapSize;i++) {
  }

 // 6. Usar munmap 
  munmap(...);

  close(fd);
}
