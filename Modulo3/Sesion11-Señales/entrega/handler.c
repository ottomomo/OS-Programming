#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


static int contador_STP=0;
static int contador_INT=0;

void handler(int signo) 
{
	char m1[80]="Recibida senal SIGTSTP\n";
	char m2[80]="Recibida senal SIGINT\n";   

	if (signo == SIGTSTP)
    {
  		write(1, m1, 80 );
		contador_STP++;        
 	}        
        
	if (signo == SIGINT)        
    {
		write(1, m2, 80 );
		contador_INT++;           
    }
} 

int main() {
	
	//VERSION 1
	//signal(SIGINT, &handler);
    //signal(SIGTSTP, &handler);

  struct sigaction act;
        
  /* Instalasmos el manejador para SIGINT y SIGTSTP */

  /* Inicializar el puntero de la funcion en act*/
  act.sa_handler = &handler;
  /* Crear el conjunto de senales en act con SIGINT y SIGTSTP*/
  sigemptyset(&act.sa_mask); //inicia  el  conjunto  de señales dado por conjunto al conjunto vacío
  sigaddset(&act.sa_mask, SIGINT);
  sigaddset(&act.sa_mask, SIGTSTP);

  /* Opciones del handler a SA_RESTART */
  act.sa_flags |= SA_RESTART;
  
  /* Instalar el controlador para las dos senales */
  if(sigaction(SIGINT,&act, NULL)==-1)
  {
  	perror("sigaction");
  	exit(-1);
  }
   if(sigaction(SIGTSTP,&act, NULL)==-1)
  {
  	perror("sigaction");
  	exit(-1);
  }

	while (contador_STP+contador_INT<10){};
    	
  printf("Se recibieron %d se񡬥s: %d SIGINT y %d SIGTSTP\n",    
  contador_STP+contador_INT,  contador_INT,contador_STP);
}
