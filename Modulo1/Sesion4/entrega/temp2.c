
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

/* Tras completar el codigo, prueba a compilarlo con diferentes niveles
de optimizacion y comprueba las diferencias de tiempo.
Trata de encontrar un codigo que requiera mas tiempo de CPU en el bucle
*/
int main()
{
	int i,j,a=0;
/* Declarar tv_ini, tv_fin, t_ini y t_fin */
        double t_ini, t_fin;
	struct timespec tv_ini, tv_fin;
	struct timeval tv_ini1, tv_fin1;

/* Obtener el tiempo actual */
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID , &tv_ini);

    for (i=0;i<10000000;i++){
	for (j=0;j<100;j++){
    		a++;
	}
    }
    
/* Obtener el tiempo actual */
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID , &tv_fin);
/* Calcular el numero de segundos total */
    
    t_ini =(double) ( tv_ini.tv_sec + ( tv_ini.tv_nsec * 1E-9) );
    t_fin =(double) ( tv_fin.tv_sec + ( tv_fin.tv_nsec * 1E-9) );    
    
/* Imprimir resultados */    
   printf("clock_gettime(CLOCK_PROCESS_CPUTIME_ID): tini=%f, tfin=%f dif=%f\n", t_ini, t_fin, (t_fin - t_ini));
	

    gettimeofday(&tv_ini1, NULL);
    a=0;
    for (i=0;i<10000000;i++){
	for (j=0;j<100;j++){
    		a++;
	}
    }

    gettimeofday(&tv_fin1, NULL);

/* Calcular el numero de segundos total */
    
    t_ini =(double) ( tv_ini1.tv_sec + ( tv_ini1.tv_usec * 1E-6) );
    t_fin =(double) ( tv_fin1.tv_sec + ( tv_fin1.tv_usec * 1E-6) );    
    
/* Imprimir resultados */    
    printf("gettimeofday(): tini=%f, tfin=%f,  dif=%f\n", t_ini, t_fin, (t_fin - t_ini));
    printf("a=%d\n",a);
    return 1;
}    
