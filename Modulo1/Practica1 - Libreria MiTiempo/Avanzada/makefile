CC=gcc

all: libTiempo.a libTiempo.so

libTiempo.a: tiempo.c

	$(CC) -c tiempo.c -o tiempo.o
	ar -rcs libTiempo.a tiempo.o

libTiempo.so: tiempo.c

	$(CC) -c -fPIC tiempo.h tiempo.c
	$(CC) -shared -fPIC -o libTiempo.so tiempo.o 
   
clean :
	rm -rf libTiempo.o
	rm -f libTiempo.so
	rm -f libTiempo.a