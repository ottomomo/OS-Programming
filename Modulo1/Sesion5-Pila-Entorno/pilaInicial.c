#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estudia el siguiente codigo e intenta 
*  prever que ocurrira cuando lo ejecutes.
*  Compila y ejecuta. ¿Observas el resultado esperado?
*  Explica que ocurre
*/
int main(int argc, char* argv[])
{

    int i;
    for (i=argc; i<10; i++) {
	if (argv[i] != NULL) {
		printf("%d: %s\n",i,argv[i]);
	}
    }	 
	
    return 1;
}            
