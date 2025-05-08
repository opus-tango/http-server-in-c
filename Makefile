all: webserver.o client_handler.o request_handler.o http_stuff.o
	gcc -o webserver.out *.o -lpthread

debug:
	gcc -g -o webserver.out webserver.c client_handler.h client_handler.c request_handler.h request_handler.c http_stuff.h http_stuff.c -lpthread

webserver: webserver.c
	gcc -c webserver webserver.c

client_handler: client_handler.c client_handler.h request_handler.h
	gcc -c client_handler client_handler.c

request_handler: request_handler.c request_handler.h http_stuff.h
	gcc -c request_handler request_handler.c

http_stuff: http_stuff.c http_stuff.h
	gcc -c http_stuff http_stuff.c

clean:
	rm -f *.o *.out