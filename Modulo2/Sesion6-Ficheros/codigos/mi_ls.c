#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

int 
main(int argc, char *argv[]) {

  struct stat buf;
  DIR   *dirp;
  struct dirent *dent;

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
  if (  == NULL) {
    perror("opendir");
    exit(1);
  }
  printf("<<<< Contenidos de %s>>>>\n",argv[1]);

/* Leemos el directorio */
  while (....) {
    printf("%s\n", ...);
  }
  
  // Cerrar directorio

}
