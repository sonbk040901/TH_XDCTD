CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 
COMMAND = ${CC} ${CFLAGS} $?
all: kplc

kplc: all_o
	${CC} main.o parser.o scanner.o reader.o charcode.o token.o error.o symtab.o semantics.o debug.o instructions.o codegen.o -o kplc

all_o: main.c scanner.c parser.c reader.c charcode.c token.c error.c symtab.c semantics.c debug.c instructions.c codegen.c
	$(COMMAND)

clean:
	rm -f *.o *~

