#include <sys/types.h>
#include <time.h>
#include <stdio.h>

int main()
{
/* Declarar t, ptr y fecha adecuadamente */
  time_t t, t_ayer;
  struct tm *tm;
  char *fecha;
  char hora[80];
  char *semana[7]={"Domingo","Lunes","Martes","Miercoles","Jueves","Viernes","Sabado"};
/* Obtencion del tiempo actual (t) */
  t=time(NULL);
/* Obtencion de la estructura  (ptr) */
  tm=localtime(&t);
/* Obtener la fecha en una cadena de la forma
   "Hoy es Martes 17:40" */
    //strftime(fecha, 100, "%w ", tm);
    strftime(hora, 100, " %H:%M", tm);
    //strftime(,80, ,);
    
/* Imprimir la cadena resultante */   
    printf("Hoy es: %s",semana[tm->tm_wday]);
    printf(" %s\n",hora);
    return 1;
} 