all: webserver.o client_handler.o request_handler.o http_stuff.o
	gcc -o webserver.out *.o -lpthread -g

webserver: webserver.c
	gcc -c webserver webserver.c -g

client_handler: client_handler.c client_handler.h request_handler.h
	gcc -c client_handler client_handler.c -g

request_handler: request_handler.c request_handler.h http_stuff.h
	gcc -c request_handler request_handler.c -g

http_stuff: http_stuff.c http_stuff.h
	gcc -c http_stuff http_stuff.c -g

clean:
	rm -f *.o *.out