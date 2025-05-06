all: webserver.o client_handler.o
	gcc -o webserver.out webserver.o client_handler.o -lpthread

webserver: webserver.c
	gcc -c webserver webserver.c

client_handler: client_handler.c
	gcc -c client_handler client_handler.c

clean:
	rm -f *.o *.out