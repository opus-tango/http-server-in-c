all: webserver.o client_handler.o request_handler.o
	gcc -o webserver.out *.o -lpthread

webserver: webserver.c
	gcc -c webserver webserver.c

client_handler: client_handler.c client_handler.h request_handler.h
	gcc -c client_handler client_handler.c

request_handler: request_handler.c request_handler.h
	gcc -c request_handler request_handler.c

clean:
	rm -f *.o *.out