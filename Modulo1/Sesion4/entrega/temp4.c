#include <time.h>
#include <stdio.h>

int main(){

/* Declarar t_hoy y tm_ptr */
	time_t t;  
	struct tm *t_hoy;
/* Obtener el tiempo hoy */    
	time (&t);
	t_hoy = localtime(&t);
/* Obtener la estructura tm_ptr*/    
   
/* Imprimir los datos indicados */
        
    printf("A–o actual:%d\n",t_hoy->tm_year+1900);
    printf("El dia del año es:%d\n", t_hoy->tm_yday);
    
    return 1;
}    
