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

#ifndef LIBMITIEMPO_H
#define LIBMITIEMPO_H
/***********************************************DECLARACION DE FUNCIONES************************************************/

/* start():
 * -Descripción: toma el instante actual como referencia para llevar la cuenta.
 * -Devuelve: en caso de éxito '0', en caso contrario '-1'.
 */
int start();

/* pause():
 * -Descripción: para temporalmente la cuenta asociada al contador. 
 * -Devuelve: Devuelve el tiempo transcurrido (en ms) desde el último resume()/start(). 
 * 	Si el contador no estaba en pausa, esta llamada se ignora.
 */
int pause(); 

/* resume():
 * -Descripción: reanuda la cuenta tras una pause(). Si el contador no estaba en pausa, esta llamada se ignora.
 * -Devuelve: el contador actual (antes de la llamada a pause()).
 */
int resume();

/* stop():
 * -Descripción: para definitivamente el contador.
 * -Devuelve: el tiempo transcurrido (en ms) desde el inicio (llamada a start()).
 */
int stop();

#endif //LIBMITIEMPO_H