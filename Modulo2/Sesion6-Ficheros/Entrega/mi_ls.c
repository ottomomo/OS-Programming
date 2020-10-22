#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

int 
main(int argc, char *argv[]) {

  struct stat buf;
  DIR   *dirp;
  struct dirent *direntp;

/* obtencion de la descripcion del directorio */
  if (stat(argv[1], &buf) == -1) {
    perror("stat");
    exit(1);
  }

/* Comprobamos que es un directorio */
  if (!S_ISDIR(buf.st_mode)) {
    fprintf(stderr, "%s no es un directorio.\n", argv[1]);
    exit(1);
  }

/* Apertura del directorio usando operdir*/
  if ( ( dirp=opendir(argv[1]) ) == NULL) {
    perror("opendir");
    exit(1);
  }
  printf("<<<< Contenidos de %s>>>>\n",argv[1]);

/* Leemos el directorio */
  printf("i-nodo\t\tnombre\n");
  while ((direntp = readdir(dirp)) != NULL) {
 	printf("%d\t\t%s\n", direntp->d_ino, /*direntp->d_off, direntp->d_reclen, */ direntp->d_name);
    //printf("%s\n", ...); %d\t%d
  }
  
  // Cerrar directorio
  closedir(dirp);
return 0;
}

/*REF: https://pasky.wordpress.com/2009/08/05/funciones-opendir-readdir-y-closedir-en-c/ */
