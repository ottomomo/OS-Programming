#include <stdio.h>
#include <signal.h>

void handler(int signo) 
{
	char m[80]="Recibida se�al SIGINT\n";   
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
  
  /* Instalar el controlador para la se�al SIGINT */
  if(sigaction(SIGINT,&act, NULL)==-1)
  {
    perror("sigaction");
    exit(-1);
  }  
  
  /* Crear el conjunto de se�ales por la que esperaremos */
  sigfillset(&seniales); //Inicializa el conjunto lleno con todas las se�ales incluidas
  sigdelset(&seniales, SIGINT); //eliminar se�ales del grupo
  
  /* Suspender el proceso */
  //La m�scara de se�ales bloqueadas se sustituye temporalmente
  //por grupo, el proceso se suspende hasta que una se�al que no este en la m�scara se produzca.
  sigsuspend(&seniales);

//--- no continua la ejecucion del programa
  printf("Continuo la ejecucion\n");
  
  return 1;
}  
//sigprocmask(SIG_UNBLOCK, &seniales, NULL); //se encargara de desbloquear las seniales marcadas