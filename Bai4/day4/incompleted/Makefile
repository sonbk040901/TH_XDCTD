CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: kplc

kplc: main.o parser.o scanner.o reader.o charcode.o token.o error.o symtab.o semantics.o debug.o
	${CC} main.o parser.o scanner.o reader.o charcode.o token.o error.o symtab.o semantics.o debug.o -o kplc -g

main.o: main.c
	${CC} ${CFLAGS} main.c

scanner.o: scanner.c
	${CC} ${CFLAGS} scanner.c

parser.o: parser.c
	${CC} ${CFLAGS} parser.c

reader.o: reader.c
	${CC} ${CFLAGS} reader.c

charcode.o: charcode.c
	${CC} ${CFLAGS} charcode.c

token.o: token.c
	${CC} ${CFLAGS} token.c

error.o: error.c
	${CC} ${CFLAGS} error.c

symtab.o: symtab.c
	${CC} ${CFLAGS} symtab.c

semantics.o: semantics.c
	${CC} ${CFLAGS} semantics.c

debug.o: debug.c
	${CC} ${CFLAGS} debug.c

clean:
	rm -f *.o *~
reMake1: kplc
	./kplc ../tests/example1.kpl 
reMake2: kplc
	./kplc ../tests/example2.kpl 
reMake3: kplc
	./kplc ../tests/example3.kpl 
reMake4: kplc
	./kplc ../tests/example4.kpl 
reMake5: kplc
	./kplc ../tests/example5.kpl 
reMake6: kplc
	./kplc ../tests/example6.kpl 