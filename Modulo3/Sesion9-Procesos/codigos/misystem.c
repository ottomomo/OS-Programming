#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

int misystem(const char *command) {
    int pid;
    int status;
    pid=fork();
    if(pid==0){
      printf("proceso hijo hace exec de %s\n", command);
      if(execl("/bin/sh", "sh", "-c", command, (char *) 0)==-1){
	perror("execl:");
	exit(-1);
      }
      exit(0);
    }else if(pid==-1){
      perror("fork:");
      exit(-1);
    }else{
      printf("el padre espera la ejecucion del hijo...\n");
      wait(&status);
      return status;
    }
}


int main(int argc, char *argv[]) {
    if(misystem(argv[1])==-1){
      perror("mysistem falló.");
      exit(-1);
    }
    return 0;
    // Uso de misystem para comprobar su funcionamiento
    // Comprueba que el proceso en curso espera hasta la finalización 
    // de la orden ejecutada en misystem
}
