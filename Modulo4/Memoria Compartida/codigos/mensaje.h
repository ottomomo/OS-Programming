#ifndef _MENSAJE_H
#define _MENSAJE_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct _dato_t
{
	char nombre[80];
    char telf[10];
};

typedef struct _dato_t dato_t;    

/* Estructura de datos que constituye el mensaje */
struct _msg_t
{
	long tipo;
    int op;
    dato_t dato;
};

typedef struct _msg_t msg_t;

/* Define para la longitud del mensaje */
#define LONG (sizeof(msg_t) - sizeof (long))

/* Define para los comandos */
#define LIST	1
#define ADD		2
#define FIN     3

/* Defines para la creacion de llaves */
#define TOK_CS	'a'
#define TOK_SC	'b'
#define KEYFILE "./mensaje.h"

#endif _MENSAJE_H
