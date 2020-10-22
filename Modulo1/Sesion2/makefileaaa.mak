CC = gcc
CFLAGS = -g -Wall
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
LDFLAGS= -lm
TARGET = $(SRC:.c=.elf)

all: $(TARGET)

%.elf: %.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -I. $(INCLUDE) -c $< -o $@

.PHONY: clean

clean: 
	rm -f $(OBJ) $(TARGET)
	
