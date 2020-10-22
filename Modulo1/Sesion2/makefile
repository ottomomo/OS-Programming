#Definicion de macros
CC = gcc				#Instruccion de compilacion.
CFLAGS = -g -Wall			#Opciones que queremos que se le pasen al compilador.
LDFLAGS = -lm	
SRC = $(wildcard *.c)			#Le dice a las reglas implícitas qué opciones usar para el linkado.
OBJ := $(patsubst %.c,%.o,$(SRC))	#Contiene los nombres de todoslos archivos de sufijo .o 
					#	que se puede generar a partir de un archivo de sufijo .c
					#	*con la funcion patsubst reemplaza los .c de la lista por .o
TARGET = $(SRC:.c=.elf)

#Definicion de reglas
default: tarea 

tarea: $(TARGET)					

%.elf: %.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf *o *elf tarea
	#rm -f $(OBJ) $(TARGET)
