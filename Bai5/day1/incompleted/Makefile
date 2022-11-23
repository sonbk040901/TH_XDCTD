CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 
COMMAND = ${CC} ${CFLAGS} $?

all: kplc

kplc: allF
	${CC} main.o parser.o scanner.o reader.o charcode.o token.o error.o symtab.o semantics.o debug.o -o kplc

allF: main.c scanner.c parser.c reader.c charcode.c token.c error.c symtab.c semantics.c debug.c
	${COMMAND}

clean:
	rm -f *.o *~
DIR = ../tests/
KPLC = ./kplc
reMake1: kplc
	${KPLC} ${DIR}example1.kpl 
reMake2: kplc
	${KPLC} ${DIR}example2.kpl 
reMake3: kplc
	${KPLC} ${DIR}example3.kpl 
reMake4: kplc
	${KPLC} ${DIR}example4.kpl 
reMake5: kplc
	${KPLC} ${DIR}example5.kpl 
reMake6: kplc
	${KPLC} ${DIR}example6.kpl 
reMake7: kplc
	${KPLC} ${DIR}example7.kpl 
reMake8: kplc
	${KPLC} ${DIR}example8.kpl 
reMake9: kplc
	${KPLC} .${DIR}example9.kpl 