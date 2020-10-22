#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
int main() {

  struct rlimit limite;

/* Obtencion del numero maximo de archivos que pueden abrirse */
  getrlimit(RLIMIT_NOFILE, &limite);
  printf("El proceso puede abrir %d archivos\n", limite.rlim_cur);

/* Fijamos el nuevo limite a 256 */
  limite.rlim_cur = 256;

  if (setrlimit(RLIMIT_NOFILE, &limite) == -1) {
     perror("setrlimit");
  }

/* Comprobacion */
  getrlimit(RLIMIT_NOFILE, &limite);
  printf("El proceso puede abrir ahora %d archivos\n", limite.rlim_cur);
  printf("Con sysconf() el numero es %d archivos\n",sysconf(_SC_OPEN_MAX));

/* CONSULTA el valor maximo de la pila e imrpimelo
 Luego trata de poner el valor al maximo (prueba con RLIM_INFINITY)
 Finalmente, trata de fijar el tam de pila a 256 bytes */
   getrlimit(RLIMIT_STACK, &limite);
   printf("El proceso puede almacenar como maxinmo %d Bytes en pila\n", limite.rlim_cur);
   
  limite.rlim_cur = RLIM_INFINITY;
/*
  if (setrlimit(RLIMIT_STACK, &limite) == -1) {
     perror("setrlimit");
  }

  getrlimit(RLIMIT_STACK, &limite);
   printf("El proceso puede almacenar como maxinmo %d en pila\n", limite.rlim_cur);*/
/* Comprobacion */
  getrlimit(RLIMIT_NOFILE, &limite);
  printf("El proceso puede abrir ahora %d archivos\n", limite.rlim_cur);
   

/* Obtencion de los limites del sistema (mediante ulimit) */
  system("ulimit -a");         
  return 0;          
}
