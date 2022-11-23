CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 
PARSER = parser
all: ${PARSER}

${PARSER}: main.o ${PARSER}.o scanner.o reader.o charcode.o token.o error.o
	${CC} main.o ${PARSER}.o scanner.o reader.o charcode.o token.o error.o -o ${PARSER}

main.o: main.c
	${CC} ${CFLAGS} main.c

scanner.o: scanner.c
	${CC} ${CFLAGS} scanner.c

${PARSER}.o: ${PARSER}.c
	${CC} ${CFLAGS} ${PARSER}.c

reader.o: reader.c
	${CC} ${CFLAGS} reader.c

charcode.o: charcode.c
	${CC} ${CFLAGS} charcode.c

token.o: token.c
	${CC} ${CFLAGS} token.c

error.o: error.c
	${CC} ${CFLAGS} error.c

clean:
	rm -f *.o *~

