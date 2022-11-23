libj.a: file.o
	gcc jval.o jrb.o dllist.o graph.o queue.o fields.o -shared -o libj.a
file.o:
	gcc -fPIC -c jval.c jrb.c dllist.c graph.c fields.c queue.c
example: gcc -shared -o libhello.so -fPIC hello.c