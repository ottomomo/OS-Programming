#include <sys/types.h>
#include <time.h>
#include <stdio.h>

int main(){

/* Declarar t_hoy, t_ayer */    
  time_t t, t_ayer;
  struct tm *tm;
  char fecha[100];
/* Tiempo actual (hoy)*/
  t=time(NULL);
  tm=localtime(&t);
  strftime(fecha, 100, "%d/%m/%Y", tm);
  
  
/* Imprimir la fecha de hoy */
  printf ("Hoy es: %s\n", fecha);

/* Calcular el tiempo ayer */
    
  t_ayer = t-86400;
  tm=localtime(&t_ayer);
  strftime(fecha, 100, "%d/%m/%Y", tm);

/* Imprimir el tiempo ayer */

  printf("Ayer fue:%s\n", fecha);    
  return 1;
}  