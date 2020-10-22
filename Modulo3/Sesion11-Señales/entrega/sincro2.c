#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define INTERCAMBIO "cola"

int contador;

void escribe_float(float num)
{
	FILE *tmp;
    
    tmp = fopen(INTERCAMBIO,"w");
    fprintf(tmp,"%f\n",num);
    fclose(tmp);
}
    
void lee_float(float *num)
{
	FILE *tmp;
    
    tmp = fopen(INTERCAMBIO,"r");
    fscanf(tmp,"%f\n",num);
    fclose(tmp);
}
void foo(int signo)
{

}
void * ini_manejador(int signal, void *manejador)
{
    struct sigaction act;
    struct sigaction old_act;

    int i;

    act.sa_handler = manejador;

    sigemptyset(&act.sa_mask);

    act.sa_flags = SA_RESTART;

    sigaction(signal, &act, &old_act);
}

int main()
{
    FILE *tmp;
    int pid;
    float num=1;        
    sigset_t seniales;
    tmp = fopen(INTERCAMBIO,"w");
    fclose(tmp);
    fprintf(tmp, "%f\n", num);
    
/* Crear el conjunto de señiales para suspender el padre 
   y el hijo hasta la recepcion de SIGUSR1 */
    sigfillset(&seniales);
    sigdelset(&seniales, SIGUSR1);
    sigdelset(&seniales, SIGINT);
    
/* Instalo un manejador para la señal */    
    ini_manejador(SIGUSR1, foo);
    
/* Bifurcar el proceso */    
    pid=fork();

/* Instalo un manejador que no hace nada por que
   cuando se recibe la señal se llama (si no accion por defecto)  ??????????????????????????????????????????*/  
	//ini_manejador(SIGUSR1,foo); 
    
    switch(pid)
    {
    	case -1:
        	perror("Error en el fork()");
            exit(-1);
            break;
        case 0:
        	
            while(1)
            {
            	/* Suspender el proceso hasta que el padre mande la señal */
                //pause();
                sigsuspend(&seniales);
		lee_float(&num);            
                num = 2.0 * num;
		escribe_float(num);
		printf("el hijo se despierta\n");
                
                /* Despertar al padre mandandole SIGUSR1, para que coja otro
                   numero */
		kill(getppid(),SIGUSR1);
            };   	
         	break;
        default:

            while(1)
            {
		lee_float(&num);			
            	printf("Resultado = %f\n",num);
		printf("introduce numero:\n");
            	scanf("%f",&num);
                printf("NUMERO = %f\n",num);
		escribe_float(num);                            
                
                /* Despertar al hijo mandandole SIGUSR1, para que procese el
                nuevo numero */
		kill(pid,SIGUSR1);
                /* Suspender el proceso hasta que el hijo nos mande
                   una señal, cuando necesite otro numero */
		//pause();
		sigsuspend(&seniales);
            }                
         	break;                
    }
}    