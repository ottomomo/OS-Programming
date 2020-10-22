//sys_errlist();
//muestra todos los posibles errores del sitema, llamar con printf.
/*
	api2.c
	@author Jorge López, Octavio Sales
*/
#include<errno.h>
#include<stdio.h>

int main () {
	
	int i;	
    	for(i=0;i<sys_nerr;++i){
    	    printf("Error num %d: %s\n", i ,sys_errlist[i]);
    	}
	return 0;
}
	
