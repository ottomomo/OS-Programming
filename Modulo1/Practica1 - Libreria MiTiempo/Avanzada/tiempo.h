/*
 * @brief: libmiTiempo.h
 * @author: Octavio Sales, Jorge López.
 */
/*
	Libreria libmiTiempo, permite la medicion de tiempos, mediante la función clock_gettime() ó gettimeofday() .

	la librería lee de un fichero de configuración qué función se usará para las medidas
	de tiempo: gettimeofday() o clock_gettime(). En caso de utilizar esta última llamada, se indicará
	también en el fichero de configuración qué fuente temporal se usará (CLOCK_REALTIME = 0, CLOCK_MONOTONIC = 1, 
	CLOCK_MONOTONIC_RAW = 2, CLOCK_PROCESS_CPUTIME_ID = 3, CLOCK_THREAD_CPUTIME_ID = 4 )
	
	Medida de tiempo utilizada: milisegundos (ms).
	
	Fichero de configuración: -Formato de fichconf: "clock_gettime [0-4];" | "gettimeofday;".
				  -El fichero tiene que estar ubicado en la ruta: "/home/usuarioso".
*/

#ifndef TIEMPO_H
#define TIEMPO_H

#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
/***********************************************DECLARACION DE VARIABLES************************************************/

#define true 1
#define false 0
	
/*
 * mi_timeid_t: estructura para medir el tiempo.
 */
typedef struct {
  int id;			// identificador de contador
  struct timespec clock_get;		// estructura para las llamadas a clock_gettime
  struct timeval gettime;		// estructura para las llamadas a gettimeofday
  double counter;		// contador donde se guarda la cuenta del tiempo transcurrido en ms.
  int paused;			//flag de estado pause
  int started;			//flag de estado start
}mi_timeid_t;
  

/***********************************************DECLARACION DE FUNCIONES************************************************/

/* createaCounter():
 * -Descripción: crea un nuevo identificador de contador.
 * -Devuelve: un id nuevo en caso de exito,  en caso contrario '-1'.
 */
mi_timeid_t createaCounter();

/* start():
 * -Descripción: toma el instante actual como referencia para llevar la cuenta. Guarda la información en la estructura time_t t pasado por parametro.
 * -Devuelve: en caso de éxito '0', en caso contrario '-1'.
 */
int start(mi_timeid_t* t);

/* pause():
 * -Descripción: para temporalmente la cuenta asociada al contador. Si el contador ya estaba en pausa, esta llamada se ignora.
 *  Guarda el tiempo transcurrido (en ms) desde el último resume()/start() en la estructura time_t t pasado por parametro.
 * -Devuelve: en caso de éxito '0', en caso contrario '-1'.	
 */
int pause(mi_timeid_t* t); 

/* resume():
 * -Descripción: reanuda la cuenta tras una pause(). Si el contador no estaba en pausa, esta llamada se ignora.
 * -Devuelve: en caso de éxito '0', en caso contrario '-1'.
 */
int resume(mi_timeid_t* t);

/* stop():
 * -Descripción: para definitivamente el contador. Guarda en time_t t el tiempo transcurrido (en ms) desde el inicio (llamada a start()).
 * -Devuelve: en caso de éxito '0', en caso contrario '-1'.
 */
int stop(mi_timeid_t* t);

#endif //TIEMPO_H