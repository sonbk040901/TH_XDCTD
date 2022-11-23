main: main.c lib
	gcc -o main main.c lkd.o jval.o jrb.o dllist.o fields.o
lib: lkd.c lkd.h jval.c jval.h jrb.c jrb.h dllist.c dllist.h fields.c fields.h
	gcc -c lkd.c jval.c jrb.c dllist.c fields.c
