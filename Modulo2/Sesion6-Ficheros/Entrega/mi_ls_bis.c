#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
int 
main(int argc, char *argv[]) {

  struct stat buf;
  DIR   *dirp;
  struct dirent *direntp;
    
    // Comprobar que argv[1] no es NULL antes usar stat
  if(argc!=2 || argv[1]==NULL){
		printf(" argumento invalido.\n");
		return -1;
   }
	   

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
  int len = strlen(argv[1]);
  char directorio[128];
  strcpy(directorio, argv[1]);
  //strncat(directorio, argv[1], len);
  char *slash ="/";
  strncat(directorio, slash, 1);

/* Leemos el directorio */
  printf("i-nodo\t\tnombre\t\tpermisos\n");
  while ((direntp = readdir(dirp)) != NULL) {
	
	 strcat(directorio, direntp->d_name);
	 if (stat(directorio, &buf)==-1)
	 {
		closedir(dirp);
		fprintf(stderr, "%s " , directorio);
	    	perror("stat ");
	     	exit(-1);
	 }
	    
 	printf("%d\t\t%s\t\t", direntp->d_ino, /*direntp->d_off, direntp->d_reclen, */ direntp->d_name);
	//printf( (S_ISDIR (buf.st_mode)) ? "d" : "-");
	printf( (buf.st_mode & S_IRUSR) ? "r" : "-");
    	printf( (buf.st_mode & S_IWUSR) ? "w" : "-");
    	printf( (buf.st_mode & S_IXUSR) ? "x" : "-");
    	printf( (buf.st_mode & S_IRGRP) ? "r" : "-");
    	printf( (buf.st_mode & S_IWGRP) ? "w" : "-");
    	printf( (buf.st_mode & S_IXGRP) ? "x" : "-");
    	printf( (buf.st_mode & S_IROTH) ? "r" : "-");
    	printf( (buf.st_mode & S_IWOTH) ? "w" : "-");
    	printf( (buf.st_mode & S_IXOTH) ? "x" : "-");
    	printf("\n");
        strcpy(directorio, argv[1]);
	strncat(directorio, slash, 1);
  }
  
  // Cerrar directorio
  closedir(dirp);
  return 0;
}


/*REF: https://pasky.wordpress.com/2009/08/05/funciones-opendir-readdir-y-closedir-en-c/ */
