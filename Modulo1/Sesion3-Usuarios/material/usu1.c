  
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>


int main()
{
/* Declarar apropiadamente las 
   variables usuario y efectivo */

/* Obtener uid del proceso */       
    usuario = ;
/* Obtener uid efectivo del proceso */    
    efectivo = ;
    
	printf("UID = %d EUID = %d\n",);
    
    if (usuario == efectivo)
    	printf("Son iguales\n",);
    else
    	printf("Interesante. UID = (%d) EUID = %d\n",);
	
    return 1;                
}    
