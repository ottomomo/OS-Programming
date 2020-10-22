#include <stdio.h>
#include <unistd.h>
/*
	api4.c
	@author Jorge L�pez, Octavio Sales
*/

int main()
{
	
    /* Obtener la informacion indicada con la funcion sysconf */
    printf("ticks/seg: %ld\n", sysconf(_SC_CLK_TCK));
    printf("Max. files: %ld\n", sysconf(_SC_OPEN_MAX));
    printf("Tama�o de pagina: %ld\n", sysconf(_SC_PAGESIZE));
    printf("Max. Hijos: %ld\n", sysconf(_SC_CHILD_MAX));
    
    return 1;
}    
