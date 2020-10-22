#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

 /* VARIABLES DE ENTORNO */
/* Codifica un programa con 2 posibles argumentos 
*  -l  (por defecto) lista el valor de todas las variabls de entorno
* -e <nombre> establece el valor de la variable EDITOR al especificado. 
*             Si la variable EDITOR ya existia previamente, 
*	      escribira por pantalla su valor anterior antes de modificarla
*
* 1. Ejecuta el codigo en un terminal y comprueba (tras la finalizacion) 
* si la variable EDITOR se ve realmente modificada ¿por que?. 
* 2. Ejecuta el codigo declarando antes (en el shell) la variable EDITOR 
* a cualquier valor. 
*/
int main(int argc, char* argv[])
{

  /* variables globales de getopt */
  extern char* optarg;
  extern int optind;
  extern int optopt;
  extern int opterr;
  opterr = 0;

  char *var, *value, string[100]="EDITOR=";
  int c;
  if((c = getopt (argc, argv, "le:")) == -1){
    printf("no hay argumentos\n");
    var="USER";
    value=getenv(var);
    printf("$USER: %s\n", value);
  }else{
	 printf("hay argumentos\n");
    switch (c)
    {
      case 'e':
	var="EDITOR";
	printf("opcion 'e'\n");
	if(value=getenv(var)==NULL){
	  printf("No existe la variable EDITOR\n");
	  strcat(string, optarg);
	  if(putenv(string)!=0){
		printf("error al crear variable: $EDITOR\n");
		return -1;
	  }
	  value=getenv(var);
	}else{
		value=getenv(var);
	   	printf("$EDITOR: %s\n", value);
		strcat(string, optarg);
	  	if(putenv(string)!=0){
			printf("error al modificar variable: $EDITOR\n");
			return -1;
	  	}
	  	value=getenv(var);
	}
	printf("$EDITOR: %s\n", value);
	break;
      case 'l':
	printf("opcion 'l'\n");
	var="USER";
	value=getenv(var);
	printf("$USER: %s\n", value);
	break;
      default:
	printf("entra en el default...\n");
	break;
    }
  }
    
    return 1;
}            
