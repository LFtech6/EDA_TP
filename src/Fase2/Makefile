#Makefile

all: programa

# Compilar o módulo grafos
grafos.o: grafos.c grafos.h structs.h
	$(CC) $(CFLAGS) -c grafos.c -o grafos.o

# Criar biblioteca estática
libgrafos.a: grafos.o
	$(AR) $(ARFLAGS) libgrafos.a grafos.o

# Compilar o programa principal com a biblioteca
programa: main.c libgrafos.a
	$(CC) $(CFLAGS) -o programa main.c -L. -lgrafos

clean:
	rm -f *.o *.a programa
