#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

  pid_t  pid;
  int    status;

  switch(pid = fork()) {   

  case -1:
    perror("fork");
    exit(1);

  case 0:
    printf("Soy el hijo\n");
    exit(23);
    
  default:
    break;
  }

  /* Usar WNOHANG para que la funcion retorne inmediatamente */
  if (waitpid(pid, &status, 0) == -1) {
    perror("waitpid");
    exit(1);
  }

  if (WIFEXITED(status))
  	printf("El hijo termino con codigo de salida %d.\n", WEXITSTATUS(status));
  if (WIFSTOPPED(status))
    printf("El hijo fue detenido por la se�al %d.\n", WSTOPSIG(status));    
  if (WIFSIGNALED(status)) 
    printf("El hijo fue terminado por la se�al %d.\n", WTERMSIG(status));
    
  return 0;
}
