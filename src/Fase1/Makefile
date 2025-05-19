#Makefile

all: programa

#módulo de funções
funcoes.o: funcoes.c funcoes.h struct.h
	$(CC) $(CFLAGS) -c funcoes.c -o funcoes.o

#biblioteca
libfuncoes.a: funcoes.o
	$(AR) $(ARFLAGS) libfuncoes.a funcoes.o

#programa principal com a biblioteca
programa: main.c libfuncoes.a
	$(CC) $(CFLAGS) -o programa main.c -L. -lfuncoes

clean:
	rm -f *.o *.a programa