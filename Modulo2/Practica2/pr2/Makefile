CC=gcc
CFLAGS=-Wall -g
SRCS=sincro.c inotify_utils.c event_queue.c copia.c
OBJS=sincro.o inotify_utils.o event_queue.o copia.o

.c.o:
	$(CC) $(CFLAGS) -c $<

all: sincro

sincro: $(OBJS)
	$(CC) $(CFLAGS) inotify_utils.o copia.o sincro.o event_queue.o -o sincro

clean:
	rm -f $(OBJS) *.bak sincro
