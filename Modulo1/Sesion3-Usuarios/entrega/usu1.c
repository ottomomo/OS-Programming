  
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
/* Declarar apropiadamente las 
   variables usuario y efectivo */
	uid_t usuario;
	gid_t efectivo;


/* Obtener uid del proceso */       
    usuario = getuid();
	printf("UID = %d\n",usuario);
/* Obtener uid efectivo del proceso */    
    efectivo = getgid();
    
	printf("UID = %d EUID = %d\n",usuario,efectivo);
    
    if (usuario == efectivo)
    	printf("Son iguales\n",usuario, efectivo);
    else
    	printf("Interesante. UID = (%d) EUID = %d\n",usuario, efectivo);
	
    return 1;                
}    

/*
El USUARIO EFECTIVO es en el que se ejecuta el proceso
y el USUARIO REAL es el que ejecuta el proceso
*/
