#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>


int main() {

  //Crea un fichero (open)
	int fd;
	fd=open("fich.txt", O_CREAT|O_WRONLY|O_TRUNC, 0664);
	struct stat statbuf;
	int status=0;
	char *path1 = "/home/usuarioso/Descargas/Sesion6-Ficheros/Entrega/fich.txt";
	char *path2 = "/home/usuarioso/Descargas/Sesion6-Ficheros/Entrega/linkFich";
	char *path3 = "/home/usuarioso/Descargas/Sesion6-Ficheros/Entrega/slink";
	close(fd);
  /* Creacion de un enlace hard */
  if(status=(link(path1, path2)==-1)){
	perror("link: ");
	exit(1);
  }

  /* Enlace simbolico */
  if(status=(symlink(path1, path3)==-1)){
	perror("symlink: ");
	exit(1);
  }
 
  // Usar lstat para ver el tamaño de ambos 
    if (lstat(path1, &statbuf) == -1) { 
	    perror("lstat"); 
	    exit(1);
    }
    printf("Tamaño del fichero original: %d bytes\n", statbuf.st_size);

    if (lstat(path2, &statbuf) == -1) { 
	    perror("lstat"); 
	    exit(1);
    }
    printf("Tamaño de el enlace rígido: %d bytes\n", statbuf.st_size);

    if (lstat(path3, &statbuf) == -1) { 
	    perror("lstat"); 
	    exit(1);
    }
    printf("Tamaño de el enlace simbolico: %d bytes\n", statbuf.st_size); 
  return 0;
}
