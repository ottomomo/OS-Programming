/*
*  Codigo de prueba1 de la libreria libmiTiempo
*/

#include <stdio.h>
#include "libmiTiempo.h"

int main(){

  int i, t;
  printf("llamada a start ...\n");
  if(start()==-1)
    return -1;
  for(i=0; i<999999999;i++){};
  t=pause();
  printf("llamada a pause: %d ms.\n", t);
  printf("llamada a resume ...\n");
  t=resume();
  printf("llamada a resume repetida ...\n");
  t=resume();
  for(i=0; i<9999999;i++){};
  t=pause();
  printf("llamada a pause: %d ms.\n", t);
  t=pause();
  printf("llamada a pause repetida: %d ms.\n", t);
  printf("llamada a resume ...\n");
  t=resume();
  for(i=0; i<9999999;i++){};
  t=stop();
  printf("llamada a stop: %d ms.\n", t);
  printf("fin del programa.\n");
  return 0;
}