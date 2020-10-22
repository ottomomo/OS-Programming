/*
	api5.c
	@author Jorge López, Octavio Sales
*/
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

/*Obtención sobre	la información del sistema	de  ficheros:	
  
–  long pathconf(char *path, int name);
–  long fpathconf(int filedes, int name);
*/

int main(){
	long result;
	/* Info del sistema de ficheros del directorio actual:*/
	printf("Info del sistema de ficheros del directorio actual:\n");
	errno = 0;
	 if ((result = pathconf("./",_PC_NAME_MAX)) == -1)
	    if (errno == 0)
	       puts("NAME_MAX has no limit.");
	    else perror("pathconf(_PC_NAME_MAX) error: ");
	 else
	    printf("Max. longitud de nombre: %ld\n", result);
	errno = 0;
	 if ((result = pathconf("./",_PC_LINK_MAX)) == -1)
	    if (errno == 0)
	       puts("_PC_LINK_MAX has no limit.");
	    else perror("pathconf(_PC_LINK_MAX) error: ");
	 else
	    printf("Max. enlaces: %ld\n", result);
	errno = 0;
	 if ((result = pathconf("./",_PC_PATH_MAX)) == -1)
	    if (errno == 0)
	       puts("_PC_PATH_MAX has no limit.");
	    else perror("pathconf(_PC_PATH_MAX) error: ");
	 else
	    printf("Max. longitud del path: %ld\n", result);

	/* Info del sistema de ficheros del directorio /dev :*/
	printf("Info del sistema de ficheros del directorio '/dev' :\n");
	errno = 0;
	 if ((result = pathconf("/dev",_PC_NAME_MAX)) == -1)
	    if (errno == 0)
	       puts("NAME_MAX has no limit.");
	    else perror("pathconf(_PC_NAME_MAX) error: ");
	 else
	    printf("Max. longitud de nombre /dev: %ld\n", result);
	errno = 0;
	 if ((result = pathconf("/dev",_PC_LINK_MAX)) == -1)
	    if (errno == 0)
	       puts("_PC_LINK_MAX has no limit.");
	    else perror("pathconf(_PC_LINK_MAX) error: ");
	 else
	    printf("Max. enlaces /dev: %ld\n", result);
	errno = 0;
	 if ((result = pathconf("/dev",_PC_PATH_MAX)) == -1)
	    if (errno == 0)
	       puts("_PC_PATH_MAX has no limit.");
	    else perror("pathconf(_PC_PATH_MAX) error: ");
	 else
	    printf("Max. longitud del path /dev: %ld\n", result);


    
	return 1;
}
