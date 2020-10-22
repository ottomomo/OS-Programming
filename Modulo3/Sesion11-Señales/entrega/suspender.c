#include <stdio.h>
#include <signal.h>

void handler(int signo) 
{
	char m[80]="Recibida señal SIGINT\n";   
  	write(1, m, 80 );
}

int main() {

  struct sigaction act;
  sigset_t seniales;
  
  /* Inicializar el puntero de la funcion */
  act.sa_handler = &handler; 
  
  /* Crear el conjunto de seniales en act a vacio */
  sigemptyset(&act.sa_mask);
  
  /* Opciones del handler a SA_RESTART */
  act.sa_flags |= SA_RESTART;
  
  /* Instalar el controlador para la señal SIGINT */
  if(sigaction(SIGINT,&act, NULL)==-1)
  {
    perror("sigaction");
    exit(-1);
  }  
  
  /* Crear el conjunto de señales por la que esperaremos */
  sigfillset(&seniales); //Inicializa el conjunto lleno con todas las señales incluidas
  sigdelset(&seniales, SIGINT); //eliminar señales del grupo
  
  /* Suspender el proceso */
  //La máscara de señales bloqueadas se sustituye temporalmente
  //por grupo, el proceso se suspende hasta que una señal que no este en la máscara se produzca.
  sigsuspend(&seniales);

//--- no continua la ejecucion del programa
  printf("Continuo la ejecucion\n");
  
  return 1;
}  
//sigprocmask(SIG_UNBLOCK, &seniales, NULL); //se encargara de desbloquear las seniales marcadas