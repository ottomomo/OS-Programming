#include <stdio.h>

/* Codigo para comprobar robustez frente a intentos de desbordar la pila */
/* 1.  
      ¿Cambiara el valor de alguna variable durante/tras la llamada a foo()? */

/* 2. Trata de forzar una Violacion de Segmento. ¿Por que se produce? */

/* 3 Trata de conseguir que cambie el valor de las variables 'despues' y/o 'antes'  sin que
     se produzca la Violacion de Segmento */

/* 4. Soluciona el problema! */

void foo() {
	unsigned char antes = 9;
	unsigned char ahora=2;
    	char nombre[16];
	unsigned char despues = 10;

	printf("antes %d (%p), ahora %d (%p) despues %d (%p) nombre %p\n",antes,&antes,ahora,&ahora,despues,&despues,nombre);
	printf("Introduce una cadena: ");
	//gets(nombre);
	fgets(nombre, 16, stdin);
	printf("cadena: %s(%p) antes %d(%p) despues %d(%p)\n",nombre,&nombre,antes,&antes,despues, &despues);
	return;

}

int main()
{
   int local = 8;
  
    printf("local antes de la llamada: %d\n",local);
    foo();
    printf("local tras la llamada: %d\n",local);

    return 1;
}            
