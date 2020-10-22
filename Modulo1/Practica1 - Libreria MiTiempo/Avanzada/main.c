/*
*  Codigo de prueba1 de la libreria libTiempo
*/

#include <stdio.h>
#include "tiempo.h"
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>

int main(){

  int i;
  mi_timeid_t t1;
  mi_timeid_t  t2;
  mi_timeid_t  t3;
  printf("llamada a start, sin crear un mi_timeid_t:\n");
  start(&t3);
  printf("Creamos t1 y t2\n");
  t1= createaCounter();
  printf("t1: id=%d, counter=%f\n", t1.id, t1.counter);
  t2= createaCounter();
  printf("t2: id=%d, counter=%f\n", t2.id, t2.counter);
  printf("llamada a start de t1 ...\n");
  if(start(&t1)==-1)
    return -1;
  printf("t1.counter: %f\n", t1.counter);
  printf("lamada a stop de t2, antes de llamar a start.\n");
  stop(&t2);
  printf("llamada a start de t2 ...\n");
  if(start(&t2)==-1)
    return -1;
  printf("t2.counter: %f\n", t2.counter);
  printf("empieza un bucle...\n");
  for(i=0; i<999999999;i++){};
  printf("termina el bucle...\n");
  if(pause(&t1)==-1)
    return -1;
  printf("llamada a pause de t1: %f ms.\n", t1.counter);
  printf("llamada a resume de t1...\n");
  if(resume(&t1)==-1)
    return -1;
  printf("volvemos a llamar a resume de t1 (se ignora la llamada)...\n");
  if(resume(&t1)==-1)
    return -1;
  if(pause(&t2)==-1)
    return -1;
  printf("llamada a pause de t2: %f ms.\n", t2.counter);
  printf("llamada a resume de t2 ...\n");
  if(resume(&t2)==-1)
    return -1;
  printf("empieza un bucle...\n");
  for(i=0; i<9999999;i++){};
  printf("termina el bucle...\n");
  if(pause(&t1)==-1)
    return -1;
  printf("llamada a pause de t1: %f ms.\n", t1.counter);
  if(pause(&t2)==-1)
    return -1;
  printf("llamada a pause de t2: %f ms.\n", t2.counter);
  if(stop(&t1)==-1)
    return -1;
  printf("llamada a stop de t1 (termina con la cuenta de pause): %f ms.\n", t1.counter);
  printf("llamada a resume de t2 ...\n");
  if(resume(&t2)==-1)
    return -1;
  printf("empieza un bucle...\n");
  for(i=0; i<9999999;i++){};
  printf("termina el bucle...\n");
  pause(&t1);
  printf("llamada a pause de t1, sin haber hecho un start() (se ignora la llamada): %f ms.\n", t1.counter);
  printf("empieza un bucle...\n");
  for(i=0; i<9999999;i++){};
  printf("termina el bucle...\n");
  if(stop(&t2)==-1)
    return -1;
  printf("llamada a stop t2: %f ms.\n", t2.counter);
  printf("fin del programa.\n");
  return 0;
}