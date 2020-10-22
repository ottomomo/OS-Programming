#include <stdio.h>
#include <sys/utsname.h>
/*
	api3.c
	@author Jorge López, Octavio Sales
*/

int main()
{
    int error;
    
    struct utsname *t;
	t = malloc(sizeof(struct utsname)); 
    
    error = uname(t); /* Obtener la informacion del sistema */
    
/* Comprobar si se ha producido un error */
    if(error==-1){
	perror("Se ha producido un error: %s\n");
	return -1;
    }
    
/* Completar con los campos adecuados */    
    printf("sistema operativo: %s\n",t->sysname);
    printf("hostname: %s\n",t->nodename);
    printf("release: %s\n",t->release);
    printf("version: %s\n",t->version);
    printf("maquina: %s\n",t->machine);        
    
    return 1;
}    
    	
    
