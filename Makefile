CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: programa

programa: main.o funcoes.o
	$(CC) $(CFLAGS) -o programa main.o funcoes.o

main.o: main.c funcoes.h
	$(CC) $(CFLAGS) -c main.c

funcoes.o: funcoes.c funcoes.h
	$(CC) $(CFLAGS) -c funcoes.c

clean:
	rm -f *.o programa
