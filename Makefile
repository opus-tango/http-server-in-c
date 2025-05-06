all: webserver.o
	gcc -o webserver.out webserver.o

webserver: webserver.c
	gcc -c webserver webserver.c

clean:
	rm -f *.o *.out