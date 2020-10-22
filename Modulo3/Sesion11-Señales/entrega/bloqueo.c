#include <signal.h>
#include <stdio.h>
#include <string.h>

void handler(int signo) 
{

  if (signo == SIGTSTP)
    {       
    }        
        
  if (signo == SIGINT)        
    { 
    }
} 

int main(int argc, char **argv)
{

	sigset_t grupo;
  sigset_t pendientes;
  int tiempo = 5; // por defecto 5s

      struct sigaction act;
      /* Inicializar el puntero de la funcion en act*/
      act.sa_handler = &handler;
      /* Crear el conjunto de senales en act con SIGINT y SIGTSTP*/
      sigemptyset(&act.sa_mask); //inicia  el  conjunto  de señales dado por conjunto al conjunto vacío
      sigaddset(&act.sa_mask, SIGINT);
      sigaddset(&act.sa_mask, SIGTSTP);

       
/* 
   Inicializar el conjunto de señales "grupo"
   con las señales de interrupcion SIGINT, y parada
   SIGTSTP
*/
    sigemptyset(&pendientes); //Inicializa el conjunto vacio
    sigemptyset(&grupo); //Inicializa el conjunto vacio
    sigaddset(&grupo, SIGINT); //añade señal al grupo
    sigaddset(&grupo, SIGTSTP); //añade señal al grupo

/* Bloquear el grupo de señales creado */

    sigprocmask (SIG_SETMASK,&grupo,NULL);

    if (argv[1]) 
	tiempo = atoi(argv[1]);
    
    //printf("Durmiendo %d segundos con (%s)\n",tiempo,comando);
    printf("Durmiendo %d segundos\n",tiempo);
    sleep(tiempo);

/* Comprobar que señales (grupo pendientes) se enviaron mientras el 
   proceso estaba dormido */

   /* Se recibio Ctrl-C ?*/
    if (sigaction(SIGINT,&act, NULL)!=-1)
    {
    	printf("Presionaste ctrl+c, no la trato\n");
    }        
    
   /* Se recibio Ctrl-Z ?*/ 
    if (sigaction(SIGTSTP,&act, NULL)!=-1)
    {
    	printf("Presionaste ctrl+z, la desbloqueo (a dormir)\n");
        /* Desbloquear la señal SIGTSTP */
        //sigedelset(&seniales, SIGINT)
        sigprocmask (SIG_UNBLOCK,&grupo,NULL);

        printf("Desperte otra vez \n");
    }            
        return 0;    
}    
