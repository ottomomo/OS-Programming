#include <sys/types.h>
#include <sys/stat.h>
#include <linux/kdev_t.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	struct stat buf;
    
    // Comprobar que argv[1] no es NULL antes usar stat
	if(argc!=2 || argv[1]==NULL){
		printf(" argumento invalido.\n");
		return -1;
	}else{  
      
	    if (stat(argv[1], &buf) == -1)
	    {
	    	perror("stat");
	     	exit(-1);
		}
	    
	    printf("Fichero: %s\n",argv[1]);
	   // printf("Dispositivo (M,m): %d, %d\n", (buf.st_dev & 0xff00) >> 8, (buf.st_dev & 0xff0000) << 8 );               
	     printf("Dispositivo (M,m): %d, %d\n", MAJOR(buf.st_dev), MINOR(buf.st_dev));
	    printf("i-nodo: %d\n", buf.st_ino);               
	   
	    // Informacion de permisos
	    // Escribir "lectura" si tiene permiso de lectura...
	    printf("Permisos del usuario: ");
	   	printf( (buf.st_mode & S_IRUSR) ? "r" : "-");
    		printf( (buf.st_mode & S_IWUSR) ? "w" : "-");
    		printf( (buf.st_mode & S_IXUSR) ? "x\n" : "-\n");
		printf("Permisos del grupo de usuario: ");
    		printf( (buf.st_mode & S_IRGRP) ? "r" : "-");
    		printf( (buf.st_mode & S_IWGRP) ? "w" : "-");
    		printf( (buf.st_mode & S_IXGRP) ? "x\n" : "-\n");
		printf("Permisos de otros: ");
    		printf( (buf.st_mode & S_IROTH) ? "r" : "-");
    		printf( (buf.st_mode & S_IWOTH) ? "w" : "-");
    		printf( (buf.st_mode & S_IXOTH) ? "x" : "-");
    		printf("\n");
	    
	    // Informacion del tipo de fichero 
	    if (S_ISDIR(buf.st_mode))
	    	printf("Tipo: Directorio\n");
		
	    if (S_ISREG(buf.st_mode))
	    	printf("Tipo: Archivo Ordinario\n");

	    if (S_ISLNK(buf.st_mode))
	    	printf("Tipo: Enlace simbolico\n");

	    // Imprimir informacion de tamanio y num bloques
		printf("Tamaño: %d bytes.\n", buf.st_size);
		printf("Tamaño en bloques: %d (bloque: 512 bytes).\n", buf.st_blocks);
	   // Imprimir informacion de tiempo	        
	  /*
		Pueden resultar utiles las funciones
		localtime, ctime,.. para manipular la informacion temporal
	    
	   */
		char* formatdate(char* str, time_t val)
		{
        		strftime(str, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
        		return str;
		}
		char date[36];
    		printf("Access: %s\n", formatdate(date, buf.st_atime));
    		printf("Modify: %s\n", formatdate(date, buf.st_mtime));
    		printf("Change: %s\n", formatdate(date, buf.st_ctime));

		return 1;
	}

}        
/* REF: http://codewiki.wikidot.com/c:system-calls:stat
   REF: https://stackoverflow.com/questions/26306644/how-to-display-st-atime-and-st-mtime */
            
